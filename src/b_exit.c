/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:51:36 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/08 11:46:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exit_num_check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if ((str[i] == '-' || str[i] == '+') && i == 0)
			{
				i++;
				if (str[i])
					continue ;
			}	
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_exit(char **s, int is_in_child, struct s_main *m_s)
{
	int exit_code;

	exit_code = 0;
	//printf("DEBUG");
	if (is_in_child == 0)
		ft_putstr_fd("exit\n", 1);
	if (s[1])
	{
		if (exit_num_check(s[1]))
		{
			exit_code = ft_atoi(s[1]);
			free_struct(m_s);
		}
		else
		{
			free_struct(m_s);
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(s[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		if (s[2])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			return (1);
		}
	}
	if (is_in_child == 0)
		free_struct(m_s);
	exit(exit_code % 256);
}
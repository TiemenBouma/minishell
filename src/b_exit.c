/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:51:36 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/12 11:23:32 by tbouma           ###   ########.fr       */
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

int count_arg(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int ft_exit(char **s, int is_in_child, struct s_main *m_s)
{
	long long exit_code;

	exit_code = 0;
	//printf("DEBUG");
	//printf("s[1] = %s\n", s[1]);

	if (is_in_child == 0)
		ft_putstr_fd("exit\n", 2);
	if (s[1])
	{
		if (exit_num_check(s[1]))
			exit_code = ft_atoi(s[1]);
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(s[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_struct(m_s);
			exit(255);
		}
		if (count_arg(s) > 2)
		{
			ft_putstr_fd("minishell: line 1: exit: too many arguments\n", 2);
			m_s->oxs = 1;
			return (1);
		}
	}
	// printf("%lld\n", exit_code);
	// printf("mod %lld\n", exit_code % 256);
	free_struct(m_s);
	exit(exit_code % 256);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:55:48 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/12 10:53:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_char_unset(char *str)
{
	if (ft_strchr(str, '=') || ft_isdigit(str[0]) || ft_strchr(str, '/'))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

int	ft_unset(t_node **list, char **exec_line)
{
	t_node	*match_node;
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	while (exec_line[i])
	{
		if (!check_char_unset(exec_line[i]))
		{
			i++;
			exit_code = 1;
			continue ;
		}
		match_node = ft_find_node_in_list(list, exec_line[i]);
		if (match_node)
			ft_remove_node(list, match_node);
		i++;
	}
	return (exit_code);
}

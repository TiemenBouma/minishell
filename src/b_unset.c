/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:55:48 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/25 08:56:09 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_char_unset(char *str)
{
	int i;
	int has_char;

	i = 0;
	has_char = 0;
	if (!ft_strchr(str, '='))
	{
		error_msg("bash: unset: : not a valid identifier", 1);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			has_char = 1;
		i++;
	}
	if (has_char == 0)
	{
		error_msg("bash: unset: : not a valid identifier", 1);
		return (0);
	}
	return (1);
}

void	ft_unset(t_node **list, /*struct	s_main	*main_struct,*/ char **exec_line)
{
	t_node	*match_node;
	char	*var_name;
	int		i;

	i = 1;
	while (exec_line[i])
	{
		if (check_char_unset(exec_line[i]))
			return ;
		var_name = make_var_name(exec_line[i]);
		match_node = ft_find_node_in_list(list, var_name);
		free(var_name);
		if (match_node)
			ft_remove_node(list, match_node);
		i++;
	}
}
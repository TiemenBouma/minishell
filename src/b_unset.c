/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:55:48 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/08 11:46:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_char_unset(char *str)
{
	if (ft_strchr(str, '=') || ft_isdigit(str[0]) || ft_strchr(str, '/'))
	{
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

void	ft_unset(t_node **list, /*struct	s_main	*m_s,*/ char **exec_line)
{
	t_node	*match_node;
	//char	*var_name;
	int		i;

	i = 1;
	//ft_env(list);
	while (exec_line[i])
	{
		if (!check_char_unset(exec_line[i]))
		{
			i++;
			continue;
		}
		//var_name = make_var_name(exec_line[i]);
		match_node = ft_find_node_in_list(list, exec_line[i]);
		//printf("matchnode= %s\n", match_node->str);
		
		//free(var_name);
		if (match_node)
		{
			ft_remove_node(list, match_node);
			//ft_env(list);
			break ;
		}
		i++;
	}
}
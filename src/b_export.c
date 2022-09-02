/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:54:09 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/02 07:42:55 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int export_num_check(char *str)
{
	return (ft_isdigit(str[0]));
}

void	print_export(t_node **list)
{
	t_node *current;

	current = *list;
	while (1)
	{
		write(1, "declare -x ", 12);
		write(1, current->str, ft_strlen(current->str));
		write(1, "\n", 1);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
}

void	ft_export(t_node **list, /*struct	s_main	*main_struct,*/ char **exec_line)
{
	t_node	*new_node;
	t_node	*match_node;
	char	*var_name;
	int	i;

	i = 1;

	if (!exec_line[1])
		print_export(list);
	else 
	{
		while (exec_line[i])
		{
			if (export_num_check(exec_line[i]))
			{
				ft_putstr_fd("bash: export: `", 2);
				ft_putstr_fd(exec_line[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				i++;
				continue;
			}
			var_name = make_var_name(exec_line[i]);
			// printf("varname= %s\n", var_name);
			match_node = ft_find_node_in_list(list, var_name);
			// if (match_node)
			// 	printf("matchnode s= %s\n", match_node->str);
			free(var_name);
			if (!match_node)
			{
				new_node = ft_new_node(exec_line[i]);
				ft_list_node_add_back(list, new_node);	
			}
			else
				replace_node_content(match_node, exec_line[i]);
			i++;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:54:09 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/12 11:23:32 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int export_num_check_equal(char *str)
{
	return (ft_isdigit(str[0]) || str[0] == '=');
}

void	print_export(t_node **list)
{
	t_node *current;

	current = *list;
	while (1)
	{
		write(1, "declare -x ", 11);
		if (ft_strchr(current->str, '=') == NULL)
		{
			write(1, current->str, ft_strlen(current->str));
			write(1, "\n", 1);
			if (current->n == NULL)
				break ;
			current = current->n;
			continue ;
		}
		write(1, current->str, ft_strchr(current->str, '=') - current->str + 1);//ft_strlen(current->str));
		write(1, "\"", 1);
		write(1, ft_strchr(current->str, '=') + 1, ft_strlen(ft_strchr(current->str, '=')) - 1);//ft_strlen(current->str));
		write(1, "\"", 1);
		write(1, "\n", 1);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
}

int	ft_export(t_node **list, /*struct	s_main	*m_s,*/ char **exec_line)
{
	t_node	*new_node;
	t_node	*match_node;
	char	*var_name;
	int	i;
	int oxs;

	i = 1;
	oxs = 0;
	if (!exec_line[1])
		print_export(list);
	else 
	{
		while (exec_line[i])
		{
			if (export_num_check_equal(exec_line[i]))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(exec_line[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				i++;
				oxs = 1;
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
	return (oxs);

}
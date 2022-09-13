/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:54:09 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/12 13:56:57 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_var_name(char *var_line)
{
	char	*var_name;
	int		i;

	i = 0;
	while (var_line[i] && var_line[i] != '=')
	{
		i++;
	}
	var_name = ft_substr(var_line, 0, i);
	if (var_name == NULL)
		exit(1);
	return (var_name);
}

int	export_num_check_equal(char *str)
{
	return (ft_isdigit(str[0]) || str[0] == '=');
}

void	print_export(t_node **list)
{
	t_node	*current;

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
		write(1, current->str, ft_strchr(current->str, '=') - current->str + 1);
		write(1, "\"", 1);
		write(1, ft_strchr(current->str, '=') + 1,
			ft_strlen(ft_strchr(current->str, '=')) - 1);
		write(1, "\"", 1);
		write(1, "\n", 1);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
}

int	input_check(char *exec_line, int *oxs, int *i)
{
	if (export_num_check_equal(exec_line))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(exec_line, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*i = *i + 1;
		*oxs = 1;
		return (0);
	}
	return (1);
}

int	ft_export(t_node **list, char **exec_line)
{
	t_node	*match_node;
	char	*var_name;
	int		i;
	int		oxs;

	i = 1;
	oxs = 0;
	if (!exec_line[1])
		print_export(list);
	else
	{
		while (exec_line[i])
		{
			if (!input_check(exec_line[i], &oxs, &i))
				continue ;
			var_name = make_var_name(exec_line[i]);
			match_node = ft_find_node_in_list(list, var_name);
			free(var_name);
			ft_add_or_change_list(list, match_node, exec_line[i]);
			i++;
		}
	}
	return (oxs);
}

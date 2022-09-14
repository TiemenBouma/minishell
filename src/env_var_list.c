/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:05:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 10:29:24 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*add_env_to_list(struct s_main *m_s, char **environ)
{
	int		i;
	t_node	*env_llist;
	t_node	*temp_node;

	i = 1;
	env_llist = ft_new_node(environ[0]);
	while (environ[i])
	{
		temp_node = ft_new_node(environ[i]);
		ft_list_node_add_back(&env_llist, temp_node);
		i++;
	}
	inc_shlvl(m_s, &env_llist);
	return (env_llist);
}

int	ft_print_var_content(t_node **list, char *var_name)
{
	t_node	*match_node;

	match_node = ft_find_node_in_list(list, var_name);
	if (match_node == NULL)
		return (0);
	ft_putstr_fd(match_node->str + ft_strlen(var_name), 2);
	write(1, "\n", 2);
	return (0);
}

void	inc_shlvl(struct s_main *m_s, t_node **list)
{
	t_node	*match_node;
	char	*var_line;

	match_node = ft_find_node_in_list(list, "SHLVL=");
	if (!match_node)
		ft_list_node_add_back(list, ft_new_node("SHLVL=1"));
	else
	{
		var_line = ft_sjf("SHLVL=",
				ft_itoa(ft_atoi(&match_node->str[6]) + 1), 2);
		if (!var_line)
			return ;
		free (match_node->str);
		match_node->str = var_line;
		m_s->minishell_nr = ft_atoi(&match_node->str[6]);
	}
}

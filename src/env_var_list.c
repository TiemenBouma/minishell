/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:05:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/27 15:19:57 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*add_env_to_list(char **environ)
{
	int i;
	t_node *env_list;
	t_node	*temp_node;

	i = 1;
	env_list = ft_new_node(environ[0]);
	while (environ[i])
	{
		temp_node = ft_new_node(environ[i]);
		ft_list_node_add_back(&env_list, temp_node);
		i++;
	}
	return (env_list);
}
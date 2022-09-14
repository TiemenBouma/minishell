/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:08:10 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 13:43:29 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_new_node(char *str)
{
	t_node	*new_node;

	new_node = malloc(sizeof (t_node));
	if (!(new_node))
		exit(1);
	new_node->str = ft_strdup(str);
	if (new_node->str == NULL)
		exit (1);
	new_node->n = NULL;
	new_node->p = NULL;
	new_node->i = -1;
	return (new_node);
}

void	ft_list_node_add_back(t_node **node_lst, t_node *new_node)
{
	t_node	*current;

	if (*node_lst == NULL)
	{
		*node_lst = new_node;
		return ;
	}
	current = *node_lst;
	while (current->n != NULL)
		current = current->n;
	current->n = new_node;
	new_node->p = current;
}

int	ft_list_size(t_node *lst)
{
	int		i;
	t_node	*current;

	if (!(lst))
		return (0);
	i = 0;
	current = lst;
	while (current != NULL)
	{
		i++;
		current = current->n;
	}
	return (i);
}

t_node	*ft_find_node_in_list(t_node **list, char *var_name)
{
	t_node	*current;
	int		len;

	current = *list;
	while (current)
	{
		len = 0;
		while (current->str[len] && current->str[len] != '=')
			len++;
		if (ft_strlen(var_name) > len)
		len = ft_strlen(var_name);
		if (!ft_strncmp(current->str, var_name, len))
			return (current);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
	return (NULL);
}

void	ft_add_or_change_list(t_node **list,
	t_node *match_node, char *exec_line)
{
	t_node	*new_node;

	if (!match_node)
	{
		new_node = ft_new_node(exec_line);
		ft_list_node_add_back(list, new_node);
	}
	else
		ft_replace_node_content(match_node, exec_line);
}

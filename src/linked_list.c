/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:08:10 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/11 07:55:39 by tbouma           ###   ########.fr       */
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
	//malloc proctect
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

t_node	*ft_list_find_last_node(t_node **list)
{
	t_node	*current;

	current = *list;
	while (current->n != NULL)
		current = current->n;
	return (current);
}

t_node *find_node_in_list(t_node **list, char *var_name)
{
	t_node *current;
	int len;

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

void	ft_find_and_remove_node(t_node **list, char *var_name)
{
	t_node	*match_node;

	match_node = find_node_in_list(list, var_name);
	if (match_node == NULL)
		return ;
	ft_remove_node(list, match_node);
}

void	ft_remove_node(t_node **list, t_node *node_to_remove)
{
	if (node_to_remove == NULL)
		return ;
	else if (node_to_remove->p == NULL && node_to_remove->n == NULL)
	{
			free(node_to_remove->str);
			free(node_to_remove);
			*list = NULL;
			return ;
	}
	else if (node_to_remove->p == NULL && node_to_remove->n)//matchnode is first.
	{
		*list = (*list)->n;
		(*list)->p = NULL;
	}
	else if (node_to_remove->p && node_to_remove->n)
	{
		node_to_remove->p->n = node_to_remove->n;
		node_to_remove->n = node_to_remove->p;
	}
	else if (node_to_remove->p && node_to_remove->n == NULL)
		node_to_remove->p->n = NULL;
	free(node_to_remove->str);
	free(node_to_remove);
}

int	replace_node_content(t_node *first_node, char *var_line)
{
	free(first_node->str);
	first_node->str = var_line; //check after implementation
	return (0);
}
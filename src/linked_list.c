/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:08:10 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/29 16:52:44 by tbouma           ###   ########.fr       */
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

t_node *find_node_in_list(t_node **list, char *var_line)
{
	t_node *current;

	current = *list;
	while (current)
	{
		if (!ft_strncmp(current->str, var_line, ft_strlen(var_line)))
			return (current);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
	return (NULL);
}

void	ft_remove_node(t_node **list, char *var_line)
{
	t_node	*match_node;
	t_node	*prev;
	t_node	*next;
	t_node	*first_node;

	prev = NULL;
	next = NULL;
	first_node = *list;
	match_node = find_node_in_list(list, var_line);
	if (match_node == NULL)
		return ;
	if (match_node->p == NULL && first_node->n)
	{
		first_node = first_node->n;
		first_node->p = NULL;

	}
	if (match_node->p)
		prev = match_node->p;
	if (match_node->n)
		next = match_node->n;
	if (prev && next)
	{
		next->p = prev;
		prev->n = next;
	}
	free(match_node->str);
	free(match_node);
}

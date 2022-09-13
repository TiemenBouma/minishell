/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 10:14:34 by tiemen        #+#    #+#                 */
/*   Updated: 2022/09/13 10:16:06 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_find_and_remove_node(t_node **list, char *var_name)
{
	t_node	*match_node;

	match_node = ft_find_node_in_list(list, var_name);
	if (match_node == NULL)
		return ;
	ft_remove_node(list, match_node);
}

void	ft_find_and_edit_node(t_node **list, char *var_name, char *content)
{
	t_node	*match_node;

	match_node = ft_find_node_in_list(list, var_name);
	if (match_node == NULL)
		return ;
	replace_node_content(match_node, content);
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
		node_to_remove->n->p = node_to_remove->p;
	}
	else if (node_to_remove->p && node_to_remove->n == NULL)
		node_to_remove->p->n = NULL;
	free(node_to_remove->str);
	free(node_to_remove);
}

int	replace_node_content(t_node *first_node, char *content) //is content malloced? otherwise we need to malloc it here.
{
	char 	*ptr;
	
	free(first_node->str);
	ptr = ft_strdup(content);
	first_node->str = ptr; //check after implementation
	return (0);
}

int	free_linked_list(t_node **list)
{
	t_node	*curr;
	t_node	*next;

	curr = *list;
	while (1)
	{
		if (curr->n)
			next = curr->n;
		free(curr->str);
		if (curr->n)
		{
			free(curr);
			curr = next;
			continue ;
		}
		else
		{
			free(curr);
			break ;
		}
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:08:10 by tbouma        #+#    #+#                 */
/*   Updated: 2022/07/28 18:33:46 by dkocob        ########   odam.nl         */
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

t_node *ft_remove_node()
{
	
}
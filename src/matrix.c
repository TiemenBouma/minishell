/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:09:00 by dkocob        #+#    #+#                 */
/*   Updated: 2022/07/17 17:00:16 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_arg_stack(struct s_data *d)
{
	struct s_line	*new;
	struct s_line	*cur;
	char			*line;
	int				i;

	i = 0;
	cur = malloc(sizeof(struct s_line));
	if (!cur || d->m.fd < 1)
		exit (0);
	while (get_next_line(d->m.fd, &line))
	{
		cur->line = line;
		if (i == 0)
			d->m.lhead = cur;
		new = malloc(sizeof(struct s_line));
		if (!new || d->m.fd < 1)
			exit (0);
		cur->next = new;
		cur = new;
		i++;
	}
	new->next = NULL;
	d->m.szy = i;
}

//expantion of variables before matrix
//{ is there variables?
// -> expand them
// -> form new tokens array
//}
// anylising inputs and ouputs redirections
// {

// return matrix.redir = malloc(sizeof(result) * ammountofpipes);
// }

void sort_tokens_for_execve(struct s_data d)
{
	int ammountofpipes = 10; //result after expantion of variables
	struct s_matrix matrix;
	
	matrix.result = malloc(sizeof(result) * ammountofpipes);
	return (result);
}
// goes to execution.c

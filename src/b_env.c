/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:58:34 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/25 08:58:56 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_node **list)
{

	t_node *current;

	current = *list;
	while (1)
	{
		write(1, current->str, ft_strlen(current->str));
		write(1, "\n", 1);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
}

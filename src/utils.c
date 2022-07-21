/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:41:42 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/21 13:03:54 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_msg(char *msg, int err)
{
	ft_putendl_fd(msg, 2);
	exit(err);
}

void	perror_msg(char *msg, int err)
{
	perror(msg);
	exit(err);
}

int free_stuff(char *str)
{
	free(str);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 09:41:42 by tiemen        #+#    #+#                 */
/*   Updated: 2022/07/20 13:56:50 by tiemen        ########   odam.nl         */
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

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	len_src;
	size_t	i;

	i = 0;
	len_src = ft_strlen(src);
	if (dest_size == 0)
		return (len_src);
	while (dest_size > 1 + i && src[i])
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	dest[i] = '\0';
	return (len_src);
}
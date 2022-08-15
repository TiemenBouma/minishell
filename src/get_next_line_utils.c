/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 02:19:45 by d                 #+#    #+#             */
/*   Updated: 2022/08/15 14:36:14 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/minishell.h"

int	ft_err(int fd, struct s_st *s)
{
	s->read[fd] = -1;
	if (s->re[fd])
	{
		s->re[fd] = (void *) 0;
		free (s->re[fd]);
	}
	if (s->tmp)
	{
		s->tmp = (void *) 0;
		free (s->tmp);
	}
	return (-1);
}

size_t	ft_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_jsf(char *s1, char *s2, int f)
{
	char	*t;

	if (!s1 || !s2)
		return ((void *) 0);
	t = malloc((int)(ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!t)
		return ((void *) 0);
	ft_strlcpy(t, s1, ft_strlen(s1) + 1);
	ft_strlcpy(t + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	if (f == 1 || f == 3)
		free(s1);
	if (f == 2 || f == 3)
		free (s2);
	return (t);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:10:41 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/15 14:36:31 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/minishell.h"

static int	ft_subline(int fd, struct s_st *s)
{
	if (s->read[fd] == -1 || !s->re[fd])
		return (ft_err(fd, s));
	s->tmp = ft_jsf("", s->re[fd] + 1, 0);
	if (!s->tmp)
		return (ft_err(fd, s));
	free (s->re[fd]);
	s->re[fd] = ft_jsf("", &s->tmp[ft_nl(s->tmp)], 0);
	if (!s->re[fd])
		return (ft_err(fd, s));
	s->tmp[ft_nl(s->tmp)] = '\0';
	if (s->read[fd] < BUFFER_SIZE && ft_strlen(s->re[fd]) == 0)
	{
		free(s->re[fd]);
		s->re[fd] = (void *) 0;
	}
	return (1);
}

static int	ft_newread(int fd, struct s_st *s)
{
	char	buffer[BUFFER_SIZE + 1];

	s->tmp = ft_jsf(s->re[fd], "", 1);
	while (1)
	{
		s->read[fd] = read(fd, buffer, BUFFER_SIZE);
		if (s->read[fd] == -1 || !s->tmp)
			return (ft_err(fd, s));
		buffer[s->read[fd]] = '\0';
		s->tmp = ft_jsf(s->tmp, buffer, 1);
		if (s->read[fd] == -1 || !s->tmp)
			return (ft_err(fd, s));
		if (ft_nl(buffer) < BUFFER_SIZE || s->read[fd] < BUFFER_SIZE)
			break ;
	}
	s->re[fd] = ft_jsf("", s->tmp, 2);
	if (s->read[fd] == -1 || !s->re[fd])
		return (ft_err(fd, s));
	return (s->read[fd]);
}

int	get_next_line(int fd, char **line)
{
	static struct s_st	s;

	if (fd >= 0 && !s.re[fd])
		s.re[fd] = ft_jsf("", "\n", 0);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !s.re[fd])
		return (-1);
	if ((int)ft_nl(s.re[fd] + 1) != ft_strlen(s.re[fd] + 1))
	{
		ft_subline(fd, &s);
		if (s.read[fd] == -1)
			return (-1);
		*line = s.tmp;
		return (1);
	}
	ft_newread(fd, &s);
	if (s.read[fd] == -1)
		return (-1);
	ft_subline(fd, &s);
	if (s.read[fd] == -1)
		return (-1);
	*line = s.tmp;
	if (s.read[fd] < BUFFER_SIZE && !s.re[fd])
		return (0);
	return (1);
}

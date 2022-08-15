/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/18 15:35:51 by dkocob        #+#    #+#                 */
/*   Updated: 2022/08/14 22:03:37 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_st
{
	char	*tmp;
	char	*re[1024];
	int		read[1024];
}t_st;
int			get_next_line(int fd, char **line);
int			ft_err(int fd, struct s_st *s);
size_t		ft_nl(char *s);
// size_t		ft_strlen(char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_jsf(char *s1, char *s2, int f);
#endif

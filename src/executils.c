/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:43:50 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/25 13:53:37 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	err_chk(int i, int t, char *s)
{
	if (i == -1 && t == 0)
	{
		write(2, "command not found\n", 18);
		exit (127);
	}
	if (i == -1 && t == 1)
	{
		perror("");
		exit (1);
	}
	if (i == -1 && t == 2)
	{
		exit (1);
	}
	if (!s)
		exit(0);
	return (-1);
}

char	*ft_sjf(char *s1, char *s2, int f)
{
	char	*t;

	if (!s1 || !s2)
		return ((void *) 0);
	t = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
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

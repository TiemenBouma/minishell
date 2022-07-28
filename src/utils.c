/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:41:42 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/28 13:38:24 by tbouma           ###   ########.fr       */
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


int	ft_strcmp_var(const char *s1, const char *s2)
{
	size_t			i;
	size_t			n;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	n = 0;
	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	i = 0;
	while (ptr1[n] && ptr1[n] != '=')
		n++;
	while (i < n && ptr1[i] && ptr2[i])
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	if (ptr1[i] == '=' && ptr2[i] == '\0')
		return (0);
	return (ptr1[i] - ptr2[i]);
}

int	is_special_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|' || c == ' ');
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 09:41:42 by tiemen        #+#    #+#                 */
/*   Updated: 2022/09/13 15:34:44 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_msg(char *msg, int err)
{
	ft_putendl_fd(msg, 2);
	return (err);
}

int	perror_msg(char *cmd, char *att, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	write(2, ": ", 2);
	ft_putstr_fd(att, 2);
	write(2, ": ", 2);
	perror(NULL);
	return (exit_status);
}

int	free_stuff(char *str)
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
	return (c == '\'' || c == '\"' || c == '<' || c == '>'
		|| c == '|' || c == ' ' || c == '/');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:41:42 by tiemen            #+#    #+#             */
/*   Updated: 2022/08/01 11:59:40 by tbouma           ###   ########.fr       */
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

// Not needed anymore
int	is_special_char_min_quotes(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ' ');
}

// ft_substr_edit checkes if there are quotest that do not need to be stored in the tokens. 
// If a quote is found it will stored it in the var 'mem' and skips that char and look for the next one,
// if it is found that char will also be skipped.
char	*ft_substr_edit(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	src_size;
	int		skiped_one;
	char	mem;

	mem = 0;
	skiped_one = 0;
	if (s == NULL)
		return (NULL);
	src_size = ft_strlen(s);
	if (start > src_size)
	{
		ptr = ft_calloc(1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	if (src_size - start < len)
		len = src_size - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	src_size = 0;
	while (s[start + src_size + skiped_one] && len > src_size)
	{
		if (mem != 0)
		{
			if (s[start + src_size + skiped_one] == mem)
			{
				skiped_one++;
				mem = 0;
				//continue ;
			}
		}
		else if ((s[start + src_size] == '\'' || s[start + src_size] == '\"'))// && skiped_one == 0)
		{
			mem = s[start + src_size + skiped_one];
			skiped_one++;
			//continue ;
		}
		ptr[src_size] = s[start + src_size + skiped_one];
		src_size++;
	}
	ptr[src_size] = '\0';
	return (ptr);
}
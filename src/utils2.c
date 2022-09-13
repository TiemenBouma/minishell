/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:30:28 by tiemen        #+#    #+#                 */
/*   Updated: 2022/09/13 15:31:57 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ft_substr_edit checkes if there are quotest that do not need
//to be stored in the tokens. 
// If a quote is found it will stored it in the var 'mem' and skips
//that char and look for the next one,
// if it is found that char will also be skipped.
static int	check_skip_quote(char c, int *mem, int *skip_quote)
{
	if (*mem != 0)
	{
		if (c == *mem)
		{
			(*skip_quote)++;
			*mem = 0;
			return (1);
		}
	}
	else if ((c == '\'' || c == '\"'))
	{
		*mem = c;
		(*skip_quote)++;
		return (1);
	}
	return (0);
}

static void	cpy_str_min_quotes(char const *s,
	unsigned int start, size_t len, char *ptr)
{
	int		mem;
	int		skip_quote;
	size_t	index;

	mem = 0;
	index = 0;
	skip_quote = 0;
	while (s[start + index + skip_quote] && len > index)
	{
		if (check_skip_quote(s[start + index + skip_quote], &mem, &skip_quote))
			continue ;
		ptr[index] = s[start + index + skip_quote];
		index++;
	}
	ptr[index] = '\0';
}

char	*ft_substr_edit(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	src_size;

	if (s == NULL)
		return (NULL);
	src_size = ft_strlen(s);
	if (start > src_size)
		return (ft_calloc(1, sizeof(char)));
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	cpy_str_min_quotes(s, start, len, ptr);
	return (ptr);
}
//-----------------------------------------------------------------

char	**make_arr_from_list(t_node **list)
{
	t_node	*current;
	int		len;
	char	**str_arr;
	int		i;

	i = 0;
	len = ft_list_size(*list);
	str_arr = malloc(sizeof(char *) * (1 + len));
	current = *list;
	while (current)
	{
		str_arr[i] = ft_strdup(current->str);
		i++;
		if (current->n == NULL)
			break ;
		current = current->n;
	}
	str_arr[len] = NULL;
	return (str_arr);
}

int	check_n_flag(char *flag)
{
	int i;

	i = 1;
	if (!flag || flag[0] != '-')
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
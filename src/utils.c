/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 09:41:42 by tiemen        #+#    #+#                 */
/*   Updated: 2022/09/13 15:03:51 by tiemen        ########   odam.nl         */
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


// ft_substr_edit checkes if there are quotest that do not need
//to be stored in the tokens. 
// If a quote is found it will stored it in the var 'mem' and skips
//that char and look for the next one,
// if it is found that char will also be skipped.

int	check_skip_quote(char c, int *mem, int *skip_quote)
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

char	*ft_substr_edit(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	src_size;
	int		skip_quote;
	int		mem;
	size_t	index;

	mem = 0;
	skip_quote = 0;
	if (s == NULL)
		return (NULL);
	src_size = ft_strlen(s);
	if (start > src_size)
		return (ft_calloc(1, sizeof(char)));
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	index = 0;
	while (s[start + index + skip_quote] && len > index)
	{
		if (check_skip_quote(s[start + index + skip_quote], &mem, &skip_quote))
			continue ;
		ptr[index] = s[start + index + skip_quote];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:02:16 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/15 15:16:47 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_string(char **str_arr, int i)
{
	while (i >= 0)
	{
		free(str_arr[i]);
		i--;
	}
	free(str_arr);
}

int	calc_len_next_str(char const *s, char c, int mem_i)
{
	int	i;

	i = 0;
	while (s[mem_i] != c && s[mem_i] != '\0')
	{
		i++;
		mem_i++;
	}
	return (i);
}

void	make_str_arr(char const *s, char c, char **str_arr, int str_count)
{
	int	current_str;
	int	i;

	current_str = 0;
	i = 0;
	while (current_str < str_count && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		str_arr[current_str] = ft_substr(s, i, (calc_len_next_str(s, c, i)));
		if (str_arr[current_str] == NULL)
			free_string(str_arr, current_str);
		while (s[i] != c && s[i])
			i++;
		current_str++;
	}
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	str_counter(char const *s, char c)
{
	int	str_count;
	int	i;

	i = 0;
	str_count = 1;
	while (s[i])
	{
		if (s[i] && is_quote(s[i]))
		{
			while (s[i] && is_quote(s[i]) == 0)
				i++;
			if (is_quote(s[i]))
				i++;
		}
		if ( s[i] && s[i] == c)
		{
			i++;
			str_count++;
		}
		if (s[i] && s[i] != c && is_quote(s[i] == 0))
			i++;
	}
	return (str_count);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	int		str_count;

	if (!s)
		return (NULL);
	str_count = str_counter(s, c);
	str_arr = (char **) malloc((str_count + 1) * sizeof(char *));
	if (str_arr == NULL)
		return (NULL);
	if (!(*s))
	{
		str_arr[0] = NULL;
		return (str_arr);
	}
	make_str_arr(s, c, str_arr, str_count);
	str_arr[str_count] = NULL;
	return (str_arr);
}
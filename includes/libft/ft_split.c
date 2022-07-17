/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:27:48 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/17 13:00:40 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_string(char **str_arr, int i)
{
	while (i >= 0)
	{
		free(str_arr[i]);
		i--;
	}
	free(str_arr);
}

static int	calc_len_next_str(char const *s, char c, int mem_i)
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

static void	make_str_arr(char const *s, char c, char **str_arr, int str_count)
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

static int	str_counter(char const *s, char c)
{
	int	str_count;
	int	i;

	i = 0;
	str_count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			str_count++;
		while (s[i] != c && s[i])
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

// int main(void)
// {
// 	char **tab = ft_split("", ' ');
// }
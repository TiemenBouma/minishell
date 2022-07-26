/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:49:14 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/26 13:25:08 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int	find_end_token(char const *s, int *index)
{
	int len;

	len = 0;
	if (s[*index] == '\'')
	{
		*index++;
		while (s[*index] && s[*index] != '\'')
		{
			len++;
			*index++;
		}
		return (len);
	}
	if (s[*index] == '\"')
	{
		index++;
		while (s[*index] && s[*index] != '\"')
		{
			len++;	
			*index++;
		}
		return (len);
	}
	if (s[*index] == '<')
	{
		while (s[*index] && s[*index] == '<')
		{
			len++;
			*index++;
		}
		return (len);
	}
	if (s[*index] == '>')
	{
		while (s[*index] && s[*index] == '>')
		{
			len++;
			*index++;
		}
		return (len);
	}
}

int	find_next_token_sign(char const *s, int *index)
{
	while (s[*index])
	{
		if (s[*index] == ' ')
			*index++;
	}
	if (s[*index] && s[*index] != ' ')
		return (1);
	return (0);
}

static int	str_counter(char const *s)
{
	int	index;
	int	count;
	
	index = 0;
	count = 0;
	while (1)
	{
		if (find_next_token_sign(s, &index))
			count++;
		else
			return (count);
		find_end_token(s, &index);
	}
}

char	**ft_split_tokens(char const *s, char c)
{
	char	**str_arr;
	int		str_count;

	if (!s)
		return (NULL);
	str_count = str_counter(s);
	str_arr = malloc(sizeof(char *) * (str_count + 1));
	if (str_arr == NULL)
		return (NULL);
	str_arr[str_count] = NULL;
	if (!(*s))
	{
		str_arr[0] = NULL;
		return (str_arr);
	}
	str_maker(s, c, str_arr);
	//str_arr[str_count] = NULL;
	return (str_arr);
}

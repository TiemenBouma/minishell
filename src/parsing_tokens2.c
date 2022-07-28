/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:49:14 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/28 13:38:40 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_end_token(char const *s, int *index)
{
	int 	len;
	char	c;

	len = 0;
	if (s[*index] == '\'' || s[*index] == '\"')
	{
		c = s[*index];
		(*index)++;
		while (s[*index] && s[*index] != c)
		{
			len++;
			(*index)++;
		}
		(*index)++;
		return (len);
	}
	else if (s[*index] == '<' || s[*index] == '>')
	{
		c = s[*index];
		while (s[*index] && s[*index] == c && len < 3)
		{
			len++;
			(*index)++;
		}
		return (len);
	}
	else if (s[*index] == '|')
	{
		len++;
		(*index)++;
		return (len);
	}
	else
	{
		while (s[*index] && !is_special_char(s[*index]))
		{
			len++;
			(*index)++;
		}
		return (len);
	}
	return (len);
}

int	find_next_token_sign(char const *s, int *index)
{
	while (s[*index] && s[*index] == ' ')
		*index = *index + 1;
	return (s[*index] != '\0');
}

static int	str_maker(char const *s, char **str_arr, int amount_of_tokens)
{
	int	index;
	int	str_len;
	int	token_n;
	int	temp_index;

	index = 0;
	token_n = 0;
	while (token_n < amount_of_tokens)
	{
		find_next_token_sign(s, &index);
		temp_index = index;
		str_len = find_end_token(s, &index);
		str_arr[token_n] = malloc(sizeof(char) * str_len + 1);
		str_arr[token_n] = NULL;
		if (s[temp_index] == '\'' || s[temp_index] == '\"')
			temp_index++;
		str_arr[token_n] = ft_substr(s, temp_index, str_len);
		token_n++;
	}
	return (0);
}

static int	str_counter(char const *s)
{
	int	index;
	int	count;
	
	index = 0;
	count = 0;
	while (s[index])
	{
		//printf("index = %d\n", index);
		if (find_next_token_sign(s, &index))
			count++;
		else
			return (count);
		find_end_token(s, &index);
		if (s[index] == '\0')
			return (count);
		//index++;
	}
	return (count);
}

char	**ft_split_tokens(char const *s)
{
	char	**str_arr;
	int		amount_of_tokens;

	if (!s)
		return (NULL);
	amount_of_tokens = str_counter(s);
	//printf("amount if tokens= %d\n", amount_of_tokens);
	str_arr = malloc(sizeof(char *) * (amount_of_tokens + 1));
	if (str_arr == NULL)
		return (NULL);
	str_arr[amount_of_tokens] = NULL;

	if (amount_of_tokens > 0)
		str_maker(s, str_arr, amount_of_tokens);
	return (str_arr);
}

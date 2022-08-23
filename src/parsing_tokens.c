/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:49:14 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/23 13:05:24 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_end_token(char const *input_str, int *index)
{
	int 	len;
	int		in_quotes;
	char	c;

	len = 0;
	in_quotes = 0;
	while (input_str[*index])
	{
		//printf("char = %c\n", input_str[*index]);
		if (input_str[*index] == '\'' || input_str[*index] == '\"')
		{
			in_quotes = 1;
			c = input_str[*index];
			(*index)++;
			while (input_str[*index] && input_str[*index] != c)
			{
				len++;
				(*index)++;
			}
			if (!input_str[*index])
				return (len);
			// if (input_str[*index])
			// 	(*index)++;
			//printf("char_in_q = %c\n", input_str[*index]);
			in_quotes = 0;

		}
		if (input_str[*index] && input_str[*index] == ' ') ///twice in this func 42 and 64
				return (len);
		else if (input_str[*index] && (input_str[*index] == '<' || input_str[*index] == '>'))
		{
			if (len > 0)
				return (len);
			c = input_str[*index];
			while (input_str[*index] && input_str[*index] == c && len <= 2)
			{
				len++;
				(*index)++;
			}
			return (len);
		}
		else if (input_str[*index] == '|')
		{
			if (len > 0)
				return (len);
			len++;
			(*index)++;
			return (len);
		}
		else if (input_str[*index] == ' ')  ///twice in this func 42 and 64
				return (len);
		else
		{
			len++;
			*index = *index + 1;
		}
			// while (input_str[*index] && !is_special_char(input_str[*index]))
			// {
			// 	len++;
			// 	(*index)++;
			// }
			// return (len);
	}
	return (len);
}

int	find_next_token_sign(char const *input_str, int *index)
{
	while (input_str[*index] && input_str[*index] == ' ')
		*index = *index + 1;
	return (input_str[*index] != '\0');
}

static int	str_maker(char const *input_str, char **str_arr, int amount_of_tokens)
{
	int	index;
	int	str_len;
	int	token_n;
	int	temp_index;

	index = 0;
	token_n = 0;
	while (token_n < amount_of_tokens)
	{
		find_next_token_sign(input_str, &index);
		temp_index = index;
		str_len = find_end_token(input_str, &index);
		//str_arr[token_n] = malloc(sizeof(char) * str_len + 1);
		str_arr[token_n] = NULL;
		if (input_str[temp_index] == '\'' || input_str[temp_index] == '\"')
			temp_index++;
		str_arr[token_n] = ft_substr_edit(input_str, temp_index, str_len);
		token_n++;
	}
	return (0);
}

static int	str_counter(char const *input_str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (input_str[index])
	{
		//printf("index = %d\n", index);
		if (find_next_token_sign(input_str, &index))
			count++;
		else
			return (count);
		find_end_token(input_str, &index);
		if (input_str[index] == '\0')
			return (count);
		//index++;
	}
	return (count);
}

char	**ft_split_tokens(char const *input_str)
{
	char	**str_arr;
	int		amount_of_tokens;

	if (!input_str)
		return (NULL);
	amount_of_tokens = str_counter(input_str);
	//printf("amount if tokens= %d\n", amount_of_tokens);
	str_arr = malloc(sizeof(char *) * (amount_of_tokens + 1));
	if (str_arr == NULL)
		return (NULL);
	str_arr[amount_of_tokens] = NULL;

	if (amount_of_tokens > 0)
		str_maker(input_str, str_arr, amount_of_tokens);
	return (str_arr);
}

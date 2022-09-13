/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_tokens.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 12:49:14 by tbouma        #+#    #+#                 */
/*   Updated: 2022/09/13 11:54:27 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_end_token(char const *input_str, int *index)
{
	int 	len;
	char	c;

	len = 0;
	while (input_str[*index])
	{
		if (input_str[*index] == '\'' || input_str[*index] == '\"')
		{
			c = input_str[*index];
			(*index)++;
			while (input_str[*index] && input_str[*index] != c)
			{
				len++;
				(*index)++;
			}
			if (input_str[*index] == c)
			{
				(*index)++;
				if (len == 0)
					return (-1);
			}
			if (!input_str[*index])
				return (len);
		}
		if (input_str[*index] && input_str[*index] == ' ') ///twice in this func 41 and 71
				return (len);
		if (input_str[*index] && (input_str[*index] == '<' || input_str[*index] == '>'))
		{
			if (len > 0)
				return (len);
			c = input_str[*index];
			while (input_str[*index] && input_str[*index] == c && len < 2)
			{
				len++;
				(*index)++;
			}
			return (len);
		}
		if (input_str[*index] == '|')
		{
			if (len > 0)
				return (len);
			len++;
			(*index)++;
			return (len);
		}
		len++;
		(*index)++;
	}
	return (len);
}

int	find_next_token_sign(char const *input_str, int *index)
{
	while (input_str[*index] && input_str[*index] == ' ')
		*index = *index + 1;
	return (input_str[*index] != '\0');
}

static int	str_maker(char const *input_str,
	char **str_arr, int amount_of_tokens)
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
		if (str_len == -1)
			continue ;
		str_arr[token_n] = NULL;
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
		if (find_next_token_sign(input_str, &index))
			count++;
		else
			return (count);
		if (find_end_token(input_str, &index) == -1)
			count--;
		if (input_str[index] == '\0')
			return (count);
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
	str_arr = malloc(sizeof(char *) * (amount_of_tokens + 1));
	if (str_arr == NULL)
		return (NULL);
	str_arr[amount_of_tokens] = NULL;

	if (amount_of_tokens > 0)
		str_maker(input_str, str_arr, amount_of_tokens);
	return (str_arr);
}

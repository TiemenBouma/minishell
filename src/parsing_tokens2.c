/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_tokens2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 13:35:09 by tiemen        #+#    #+#                 */
/*   Updated: 2022/09/13 13:45:21 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_double_arrow(char const *input_str, int *index, int *len)
{
	char	c;

	if (input_str[*index] && (input_str[*index]
			== '<' || input_str[*index] == '>'))
	{
		if (*len > 0)
			return (1);
		c = input_str[*index];
		while (input_str[*index] && input_str[*index] == c && *len < 2)
		{
			(*len)++;
			(*index)++;
		}
		return (1);
	}
	return (0);
}

int	find_end_quote(char const *input_str, int *index, int *len)
{
	char	c;

	if (input_str[*index] == '\'' || input_str[*index] == '\"')
	{
		c = input_str[*index];
		(*index)++;
		while (input_str[*index] && input_str[*index] != c)
		{
			(*len)++;
			(*index)++;
		}
		if (input_str[*index] == c)
		{
			(*index)++;
			if ((*len) == 0)
			{
				*len = -1;
				return (1);
			}
		}
		if (!input_str[*index])
			return (1);
	}
	return (0);
}

int	find_end_token(char const *input_str, int *index)
{
	int		len;

	len = 0;
	while (input_str[*index])
	{
		if (find_end_quote(input_str, index, &len))
			return (len);
		if (input_str[*index] && input_str[*index] == ' ')
			return (len);
		if (check_double_arrow(input_str, index, &len))
			return (len);
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

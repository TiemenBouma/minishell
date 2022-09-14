/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:36:52 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 11:04:49 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*func1(char *input, int *index, char *temp)
{
	int	s;
	int	l;

	(*index)++;
	if (input[*index] == '\0' || input[*index] == ' ')
		return (temp);
	s = *index;
	l = find_len_var_name(&input, s);
	temp = ft_substr(input, s, l);
	return (temp);
}

/*
s = s
l = len
*/
static char	*find_next_var_in_str(char *input, int *index)
{
	char	*temp;
	int		in_quotes;
	//char	c;

	temp = NULL;
	in_quotes = 0;
	while (input[*index])
	{
		// c = is_open_quote(input[*index], &in_quotes, index, &c);
		// if (!is_close_single_quote(&in_quotes, index, &c, input))
		// 	return (temp);
		// if (input[*index] && c == input[*index] && in_quotes == 1)
		// {
		// 	c = 0;
		// 	in_quotes = 0;
		// }
		if (input[*index] && input[*index] == '$')
			return (func1(input, index, temp));
		if (input[*index])
			(*index)++;
	}
	return (temp);
}

int	expand_variables_heredoc(char **input, t_node **list, int oxs)
{
	int		index;
	char	*v_name;
	char	*content;
	char	*str_exit_status;

	index = 0;
	while ((*input)[index])
	{
		v_name = find_next_var_in_str(*input, &index);
		if (v_name == NULL)
		{
			if (!(*input)[index])
				break ;
			index++;
			continue ;
		}
		content = find_var_in_list(list, v_name);
		if (ft_strncmp(v_name, "?", 2) == 0)
		{
			str_exit_status = ft_itoa(oxs);
			replace_input(input, str_exit_status, &index, v_name);
			free(str_exit_status);
		}
		else if (content == NULL)
			replace_input(input, "", &index, v_name);
		else
		{	
			replace_input(input, content, &index, v_name);
			index++;
		}
		free(v_name);
	}
	return (0);
}
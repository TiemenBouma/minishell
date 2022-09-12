/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:14:11 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/12 15:57:48 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_close_single_quote(int *in_q, int *index, char *old_c, char *input)
{
	if (*old_c == '\'' && *in_q == 1)
	{
		while (input[*index] && input[*index] != '\'')
			(*index)++;
		*old_c = 0;
		if (!input[*index])
			return (0);
	}
	return (1);
}

char	is_open_quote(char curr_c, int *in_quotes, int *index, char *old_c)
{
	if (*in_quotes == 1)
		return (*old_c);
	if ((curr_c == '\"' || curr_c == '\'') && *in_quotes == 0)
	{
		(*index)++;
		*in_quotes = 1;
		return (curr_c);
	}
	return (0);
}

char	*func1(char *input, int *index, char *temp)
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
char	*find_next_var_in_str(char *input, int *index)
{
	char	*temp;
	int		in_quotes;
	char	c;

	temp = NULL;
	in_quotes = 0;
	while (input[*index])
	{
		c = is_open_quote(input[*index], &in_quotes, index, &c);
		if (!is_close_single_quote(&in_quotes, index, &c, input))
			return (temp);
		if (input[*index] && c == input[*index] && in_quotes == 1)
		{
			c = 0;
			in_quotes = 0;
		}
		if (input[*index] && input[*index] == '$')
			return (func1(input, index, temp));
		if (input[*index])
			(*index)++;
	}
	return (temp);
}

int	expand_variables(char **input, t_node **list, int oxs)
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

// void	expand_variables(char **input, struct s_main *m_s, int index)
// {
// 	char	*v_name;
// 	char	*content;

// 	while ((*input)[index])
// 	{
// 		v_name = find_next_var_in_str(*input, &index);
// 		if (v_name == NULL)
// 		{
// 			if (!(*input)[index])
// 				break ;
// 			index++;
// 			continue ;
// 		}
// 		content = find_var_in_list(&m_s->env_llist, v_name);
// 		if (ft_strncmp(v_name, "?", 2) == 0)
// 			replace_input(input, ft_itoa(m_s->oxs), &index, v_name);
// 		else if (content == NULL)
// 			replace_input(input, "", &index, v_name);
// 		else
// 		{	
// 			replace_input(input, content, &index, v_name);
// 			index++;
// 		}
// 		free(v_name);
// 	}
// }

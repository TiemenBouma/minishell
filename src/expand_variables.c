/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:14:11 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/15 10:19:06 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_close_quote(int *c, int *in_q, int *index, char *input)
{
	if (*c == '\'' && *in_q == 1)
	{
		//printf("DEBUG1 index = %d\n", *index);
		while (input[*index] && input[*index] != '\'')
			(*index)++;
		*in_q = 0;
		*c = 0;
		if (!input[*index])
			return (0);
	}
	if (*c == '\"' && *c == input[*index] && *in_q == 1)
	{
		(*index)++;
		*in_q = 0;
		*c = 0;
		if (!input[*index])
			return (0);
	}
	return (1);
}

int	is_open_quote(int *c, int *in_quotes, int *index, char input_char)
{
	// if (*c != 0)
	// 	return (1);
	if ((input_char == '\"' || input_char == '\'') && *in_quotes == 0)
	{
		*c = input_char;
		(*index)++;
		*in_quotes = 1;
		return (1);
	}
	return (0);
}

static char	*make_var_name_ex(char *input, int *index, char *temp)
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
static char	*find_next_var_in_str(char *input, int *index, int *c, int *in_quotes)
{
	char	*temp;

	temp = NULL;
	while (input[*index])
	{
		is_open_quote(c, in_quotes, index, input[*index]);
		if (!is_close_quote(c, in_quotes, index,  input))
			return (temp);
		// if (input[*index] && c == input[*index] && in_quotes == 1)
		// {
		// 	c = 0;
		// 	in_quotes = 0;
		// }
		if (input[*index] && input[*index] == '$')
			return (make_var_name_ex(input, index, temp));
		if (input[*index])
			(*index)++;
	}
	return (temp);
}

void	expand_variables(char **input, t_node **list, int oxs, int index)
{
	char	*v_name;
	int		c;
	int		in_quotes;

	c = 0;
	in_quotes = 0;
	while ((*input)[index])
	{
		//printf("input s = %c inddex = %d\n", (*input)[index], index);
		v_name = find_next_var_in_str(*input, &index, &c, &in_quotes);
		if (v_name == NULL)
		{
			if (!(*input)[index])
				break ;
			index++;
			continue ;
		}
		if (ft_strncmp(v_name, "?", 2) == 0)
			replace_input(input, ft_itoa(oxs), &index, v_name);
		else if (find_var_in_list(list, v_name) == NULL)
			replace_input(input, ft_calloc(sizeof(1), 1), &index, v_name);
		else
		{	
			replace_input(input, ft_strdup(find_var_in_list(list, v_name)),
				&index, v_name);
			index++;
		}
		free(v_name);
	}
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

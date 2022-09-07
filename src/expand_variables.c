/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:14:11 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/07 15:18:30 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	calc_len_new_str(char **input, char *content, char *v_name)
{
	return (ft_strlen(*input) + (ft_strlen(content) - ft_strlen(v_name)));
}

/*
s = s
l = len
in = input_str/input
*/
int	replace_input(char **in, char *content, int *i, char *v_name)
{
	int		s;
	int		l;
	int		len_new_str;
	char	*temp1;
	char	*temp2;

	l = 0;
	s = *i;
	len_new_str = calc_len_new_str(in, content, v_name);
	while ((*in)[s + l] && !is_special_char((*in)[s + l]))
		l++;
	temp1 = ft_substr(*in, 0, s - 1);
	if ((*in)[s + l] == ' ')
		temp2 = ft_substr(*in, s + l, ft_strlen(*in + s + l));
	else
		temp2 = ft_substr(*in, s + ft_strlen(v_name), ft_strlen(*in + s + l));	
	free(*in);
	*in = ft_calloc(sizeof(char), (len_new_str + 1));
	if (*in == NULL)
		exit (1); //malloc protection, do we want to exit? (Tiemen)
	ft_memcpy(*in, temp1, ft_strlen(temp1));
	ft_strlcat(*in, content, len_new_str);
	ft_strlcat(*in, temp2, len_new_str);
	return (0);
}

char	*find_var_in_list(t_node **list, char *v_name)
{
	t_node	*current;

	current = *list;
	while (1)
	{
		if (!ft_strcmp_var(current->str, v_name))
			return (current->str + 1 + ft_strlen(v_name));
		if (current->n == NULL)
			break ;
		current = current->n;
	}	
	return (NULL);
}

// int	is_dollar()
// {
	
// }

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
/*
s = s
l = len
*/
char	*find_next_var_in_str(char *input, int *index)
{
	int		s;
	int		l;
	char	*temp;
	int		in_quotes;
	char	c;

	temp = NULL;
	in_quotes = 0;
	l = 0;
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
		{
			(*index)++;
			if (input[*index] == '\0' || input[*index] == ' ')// || input[*index] == '/')
				return (temp);
			s = *index;
			while (input[s + l] && !is_special_char(input[s + l]))// && input[s + l] !=  '/')
				l++;
			temp = ft_substr(input, s, l);
			return (temp);
		}
		if (input[*index])
			(*index)++;
	}
	return (temp);
}

int	expand_variables(char **input, t_node **list, int old_exit_status)
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
		}	//return (0);
		content = find_var_in_list(list, v_name);
		if (v_name[0] == '?')
		{
			str_exit_status = ft_itoa(old_exit_status);
			replace_input(input, str_exit_status, &index, v_name);
			free(str_exit_status);
		}
		else if (content == NULL)
			replace_input(input, "", &index, v_name);//continue ;
		else
		{	
			replace_input(input, content, &index, v_name);
			index++;
		}
	}
	return (0);
}
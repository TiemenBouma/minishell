/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:06:03 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/12 15:57:49 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char_var_expand(char c)
{
	return (c == '<' || c == '>' || c == '|'
		|| c == ' ' || c == '/' || c == '=' || c == '\'' || c == '\"');
}

int	calc_len_new_str(char **input, char *content, char *v_name)
{
	return (ft_strlen(*input) + (ft_strlen(content) - ft_strlen(v_name)));
}

int	find_len_var_name(char **in, int s)
{
	int	l;

	l = 0;
	while ((*in)[s + l] && !is_special_char_var_expand((*in)[s + l]))
	{
		if (l == 0 && (*in)[s + l] == '?')
		{
			l++;
			break ;
		}
		l++;
	}
	return (l);
}

/*
s = s
l = len
in = input_str/input
*/
void	replace_input(char **in, char *content, int *i, char *v_name)
{
	int		s;
	int		l;
	int		len_new_str;
	char	*temp1;
	char	*temp2;

	s = *i;
	len_new_str = calc_len_new_str(in, content, v_name);
	l = find_len_var_name(in, s);
	temp1 = ft_substr(*in, 0, s - 1);
	if ((*in)[s + l] == ' ')
		temp2 = ft_substr(*in, s + l, ft_strlen(*in + s + l));
	else
		temp2 = ft_substr(*in, s + ft_strlen(v_name), ft_strlen(*in + s + l));
	free(*in);
	*in = ft_calloc(sizeof(char), (len_new_str + 1));
	if (*in == NULL)
		exit (1);
	(*in)[len_new_str] = '\0';
	ft_memcpy(*in, temp1, ft_strlen(temp1));
	ft_strlcat(*in, content, len_new_str);
	ft_strlcat(*in, temp2, len_new_str);
	//free(content);
	free(temp1);
	free(temp2);
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
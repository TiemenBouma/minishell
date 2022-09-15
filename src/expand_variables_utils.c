/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:06:03 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/15 11:39:12 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char_var_expand(char c)
{
	return (c == '<' || c == '>' || c == '|' ||  c == '$'
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

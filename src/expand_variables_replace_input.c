/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_replace_input.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:29:50 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/15 11:38:39 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	calc_len_new_str(char **input, char *content, char *v_name);
int	is_special_char_var_expand(char c);
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
	//*i = *i + ft_strlen(content) - 1;
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
	free(temp1);
	free(temp2);
	free(content);
}

void	replace_input1(struct s_main *m_s, char *v_name, int *index)
{
	if (ft_strncmp(v_name, "?", 2) == 0)
		replace_input(&m_s->input_str, ft_itoa(m_s->oxs), index, v_name);
	else if (find_var_in_list(&m_s->env_llist, v_name) == NULL)
		replace_input(&m_s->input_str, ft_calloc(sizeof(1), 1), index, v_name);
	else
	{	
		replace_input(&m_s->input_str,
			ft_strdup(find_var_in_list(&m_s->env_llist, v_name)),
			index, v_name);
		index++;
	}
}

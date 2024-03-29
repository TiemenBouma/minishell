/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:36:52 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/23 09:49:43 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*make_var_name_here(char *input, int *index, char *temp)
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

	temp = NULL;
	while (input[*index])
	{
		if (input[*index] && input[*index] == '$')
			return (make_var_name_here(input, index, temp));
		if (input[*index])
			(*index)++;
	}
	return (temp);
}

void	expand_variables_heredoc(char **input,
	t_node **list, int oxs, int index)
{
	char	*v_name;

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
		if (find_var_in_list(list, v_name) == NULL)
			replace_input(input, ft_calloc(sizeof(1), 1), &index, v_name);
		else if (ft_strncmp(v_name, "?", 2) == 0)
			replace_input(input, ft_itoa(oxs), &index, v_name);
		else
		{	
			replace_input(input, ft_strdup(find_var_in_list(list, v_name)),
				&index, v_name);
			index++;
		}
		free(v_name);
	}
}
// 	int		index;
// 	char	*v_name;
// 	char	*content;
// 	char	*str_exit_status;

// 	index = 0;
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
// 		content = find_var_in_list(list, v_name);
// 		if (ft_strncmp(v_name, "?", 2) == 0)
// 		{
// 			str_exit_status = ft_itoa(oxs);
// 			replace_input(input, str_exit_status, &index, v_name);
// 			free(str_exit_status);
// 		}
// 		else if (content == NULL)
// 			replace_input(input, "", &index, v_name);
// 		else
// 		{	
// 			replace_input(input, content, &index, v_name);
// 			index++;
// 		}
// 		free(v_name);
// 	}
// 	return (0);
// }

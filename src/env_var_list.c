/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:05:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/02 10:25:57 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_node	*add_env_to_list(char **environ)
{
	int i;
	t_node *env_list;
	t_node	*temp_node;

	i = 1;
	env_list = ft_new_node(environ[0]);
	while (environ[i])
	{
		temp_node = ft_new_node(environ[i]);
		ft_list_node_add_back(&env_list, temp_node);
		i++;
	}
	return (env_list);
}

char	*find_var_in_list(t_node **list, char *var_name)
{
	t_node	*current;

	current = *list;
	while (current->n != NULL)
	{
		if (!ft_strcmp_var(current->str, var_name))
			return (current->str + 1 + ft_strlen(var_name));
		current = current->n;
		if (current->n == NULL)
			break ;
	}	
	return (NULL);
}

char	*find_next_var_in_str(char *input_str, int *index)
{
	//int	i;
	int start;
	int len;
	char	*temp;

	temp = NULL;
	//i = index;
	len = 0;
	while (input_str[*index])
	{
		//printf("\ndebug\n\n");
		if (input_str[*index] == '\'')
		{
			*index = *index + 1;
			while (input_str[*index] && input_str[*index] != '\'')
				(*index)++;
		}
		if (input_str[*index] == '$')
		{
			(*index)++;
			if (input_str[*index] == '\0')
				return (temp);
			start = *index;
			while (input_str[start + len] && !is_special_char(input_str[start + len]))
				len++;
			temp = ft_substr(input_str, start, len);
			return (temp);
		}
		*index = *index + 1;
		//*index = len + start;
	}
	return (temp);
}

int	calc_len_new_str(char **input_str, char *content, char *var_name)
{
	return (ft_strlen(*input_str) + (ft_strlen(content) - ft_strlen(var_name)));
}

int	replace_input_str(char **input_str, char *content, int *index, char *var_name)
{
	int start;
	int len;
	int len_new_str;
	char	*temp1;
	char	*temp2;

	len = 0;
	start = *index;
	//printf("old input string = %s\n", *input_str);
	len_new_str = calc_len_new_str(input_str, content, var_name);
	while ((*input_str)[start + len] && !is_special_char((*input_str)[start + len]))
		len++;
	temp1 = ft_substr(*input_str, 0, start - 1);
	
	//printf("start = %d\n", start);
	//printf("str_len var_name = %d\n", ft_strlen(var_name));
	// printf("char = %c\n", (*input_str)[start + len]);
	if ((*input_str)[start + len] == ' ')
		temp2 = ft_substr(*input_str, start + len, ft_strlen(*input_str + start + len));
	else
		temp2 = ft_substr(*input_str, start + ft_strlen(var_name), ft_strlen(*input_str + start + len));
	free(*input_str);
	*input_str = ft_calloc(sizeof(char), (len_new_str + 1));
	//malloc protection
	// ft_memset(*input_str, '\0', len_new_str);
	// *input_str[len_new_str] = '\0';
	// printf("temp1 = %s\n", temp1);
	// printf("contect = %s\n", content);
	// printf("temp2 = %s\n", temp2);
	ft_memcpy(*input_str, temp1, ft_strlen(temp1));
	ft_strlcat(*input_str, content, len_new_str);
	ft_strlcat(*input_str, temp2, len_new_str);
	//printf("new input string = %s\n", *input_str);
	return (0);
}

int	expand_var(char **input_str, t_node **list)
{
	int 	index;
	char	*var_name;
	char	*content;

	index = 0;
	while ((*input_str)[index])
	{
		var_name = find_next_var_in_str(*input_str, &index);
		if (var_name == NULL)
			return (0);
		content = find_var_in_list(list, var_name);
		if (content == NULL)
			continue ;
		replace_input_str(input_str, content, &index, var_name);
		index++;
	}
	return (0);
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:05:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/23 13:36:59 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_node	*add_env_to_list(char **environ)
{
	int i;
	t_node *env_llist;
	t_node	*temp_node;

	i = 1;
	env_llist = ft_new_node(environ[0]);
	while (environ[i])
	{
		temp_node = ft_new_node(environ[i]);
		ft_list_node_add_back(&env_llist, temp_node);
		i++;
	}
	return (env_llist);
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
	int		in_quotes;

	temp = NULL;
	in_quotes = 0;
	//i = index;
	len = 0;
	while (input_str[*index])
	{
		//printf("\ndebug\n\n");
		if (input_str[*index] == '\"' && in_quotes == 0)
		{
			(*index)++;
			in_quotes = 1;
		}
		if (input_str[*index] == '\"' && in_quotes == 1)
		{
			(*index)++;
			in_quotes = 0;
		}
		if (input_str[*index] == '\'' && in_quotes == 0)
		{
			*index = *index + 1;
			while (input_str[*index] && input_str[*index] != '\'')
				(*index)++;
			if (!input_str[*index])
				return (temp);
		}
		if (input_str[*index] == '$')
		{
			//printf("index == %d\n", *index);
			// if (input_str[*index + 1] && (input_str[*index + 1] == ' ' || ))
			// {
			// 	return NULL;// *index = *index + 1;
			// 	// continue;
			// }
			(*index)++;
			if (input_str[*index] == '\0' || input_str[*index] == ' ')
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

int	expand_variables(char **input_str, t_node **list, int old_exit_status)
{
	int 	index;
	char	*var_name;
	char	*content;
	char	*str_exit_status;

	index = 0;
	while ((*input_str)[index])
	{
		var_name = find_next_var_in_str(*input_str, &index);
		if (var_name == NULL)
		{
			if (!(*input_str)[index])
				break ;
			index++;
			continue ;
		}	//return (0);
		content = find_var_in_list(list, var_name);
		if (var_name[0] == '?')
		{
			str_exit_status = ft_itoa(old_exit_status);
			replace_input_str(input_str, str_exit_status, &index, var_name);
			free(str_exit_status);
		}
		else if (content == NULL)
			replace_input_str(input_str, "", &index, var_name);//continue ;
		else
		{	
			replace_input_str(input_str, content, &index, var_name);
			index++;
		}
	}
	return (0);
}

int	ft_print_var_content(t_node **list, char *var_name)
{
	t_node	*match_node;
	
	match_node = ft_find_node_in_list(list, var_name);
	if (match_node == NULL)
		return (0);
	ft_putstr_fd(match_node->str + ft_strlen(var_name), 2);
	write(1, "\n", 2);
	return (0);
}

void	inc_shlvl(t_node **list)
{
	t_node	*match_node;
	char	*var_line;

	match_node = ft_find_node_in_list(list, "SHLVL=");
	
	if (!match_node)
		ft_list_node_add_back(list, ft_new_node("SHLVL=1"));
	else
	{
		var_line = ft_sjf("SHLVL=", ft_itoa(ft_atoi(&match_node->str[6]) + 1), 0);
		if (!var_line)
			return ;
		free (match_node->str);
		match_node->str = var_line;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:56:02 by tiemen            #+#    #+#             */
/*   Updated: 2022/08/11 13:34:31 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_path(t_node **list)
{
	char	*ptr;
	char	**root_paths;
	t_node	*match_node;

	match_node = ft_find_node_in_list(list, "PATH=");
	if (match_node == NULL)
	{
		error_msg(ERR_PATH, 1);
		return (NULL);	
	}
	ptr = match_node->str + 5;
	root_paths = ft_split(ptr, ':');
	if (root_paths == NULL)
		error_msg(ERR_MALLOC, 1);
	return (root_paths);
}

int	add_path(char **exec_line, char **root_paths)
{
	char	*temp;
	char	*temp2;
	char	*cmd_temp;
	int		i;

	i = 0;
	if (root_paths == NULL)
		return (0);
	if (access(exec_line[0], F_OK) == 0)
		return (0);
	cmd_temp = ft_strdup(exec_line[0]);
	if (is_builtin(exec_line[0])) //New feature, checking on buildin
		return (0);
	while (root_paths[i])
	{
		temp = ft_strjoin(root_paths[i], "/");
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		temp2 = ft_strjoin(temp, cmd_temp);
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(exec_line[0]);
		exec_line[0] = temp2;
		free(temp);
		//free(temp2);
		if (access(exec_line[0], F_OK) == 0)
		{
			free(cmd_temp);
			return (0);
		}
		i++;
	}
		
	// if the command is EXIT and maybe other commands need to be handeld here. (See begin func for handeling buildins)
	
	free(exec_line[0]);
	exec_line[0] = cmd_temp;
	//error_msg(ERR_CMD, 127);
	return (0);
}

// int	find_cmd_in_line(char **cmd_line)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_line[i])
// 	{
// 		if (cmd[i][0] == '<' || cmd[i][0] == '>')
// 		{
// 			if (cmd[i] && cmd[i + 1])
// 				i += 2;
// 		}
// 	}
// }

// char	***add_path_to_cmd(char ***cmd_lines, char **root_paths)
// {
// 	int	i;
// 	int	cmd_count;
// 	char	***exec_lines;

// 	i = 0;
// 	cmd_count = 4;//needs function to know or get from struct form parse tokens
// 	exec_lines = malloc(sizeof(char **) * (cmd_count + 1));
// 	while (i < cmd_count)
// 	{
// 		find_cmd_in_line(cmd_lines[i]);
// 		exec_lines[i] = find_cmd_path(exec_lines[i], root_paths, cmd_lines[i][0]);
// 		i++;
// 	}
	
	
// }


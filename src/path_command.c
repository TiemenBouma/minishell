/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:56:02 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/21 17:49:03 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_path(char **envp)
{
	char	*ptr;
	char	**root_paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		ptr = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (ptr != NULL)
			break ;
		i++;
	}
	if (ptr == NULL)
		error_msg(ERR_PATH, 1);
	ptr += 5;
	root_paths = ft_split(ptr, ':');
	if (root_paths == NULL)
		error_msg(ERR_MALLOC, 1);
	return (root_paths);
}

char	*find_cmd_path(char **path_and_cmd_line, char **root_paths, char *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
	{
		path_and_cmd_line[0] = ft_strdup(cmd);
		return (path_and_cmd_line[i]);
	}
	while (root_paths[i])
	{
		temp = ft_strjoin(root_paths[i], "/");
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		//free(root_paths[i]);
		path_and_cmd_line[0] = temp;
		temp = ft_strjoin(root_paths[i], cmd);
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(path_and_cmd_line[0]);
		path_and_cmd_line[0] = temp;
		if (access(path_and_cmd_line[0], F_OK) == 0)
			return (path_and_cmd_line[0]);
		i++;
	}
	error_msg(ERR_CMD, 127);
	return (0);
}

int	find_cmd_in_line(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
		{
			if (cmd[i] && cmd[i + 1])
				i += 2;
		}
	}
}

char	***add_path_to_cmd(char ***cmd_lines, char **root_paths)
{
	int	i;
	int	cmd_count;
	char	***path_and_cmd_lines;

	i = 0;
	cmd_count = 4;//needs function to know or get from struct form parse tokens
	path_and_cmd_lines = malloc(sizeof(char **) * (cmd_count + 1));
	while (i < cmd_count)
	{
		find_cmd_in_line(cmd_lines[i]);
		path_and_cmd_lines[i] = find_cmd_path(path_and_cmd_lines[i], root_paths, cmd_lines[i][0]);
		i++;
	}
	
	
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_comand.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 09:56:02 by tiemen        #+#    #+#                 */
/*   Updated: 2022/07/14 10:02:40 by tiemen        ########   odam.nl         */
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
		ptr = ft_strnstr(envp[i], "PATH=", strlen(envp[i]));
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

char	*find_cmd_path(char **root_paths, char *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (root_paths[i])
	{
		temp = ft_strjoin(root_paths[i], "/");
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(root_paths[i]);
		root_paths[i] = temp;
		temp = ft_strjoin(root_paths[i], cmd);
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(root_paths[i]);
		root_paths[i] = temp;
		if (access(root_paths[i], F_OK) == 0)
			return (root_paths[i]);
		i++;
	}
	error_msg(ERR_CMD, 127);
	return (0);
}


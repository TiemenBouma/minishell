/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:56:02 by tiemen            #+#    #+#             */
/*   Updated: 2022/09/07 10:47:12 by tbouma           ###   ########.fr       */
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
		return (NULL);
	ptr = match_node->str + 5;
	root_paths = ft_split(ptr, ':');
	if (root_paths == NULL)
		error_msg(ERR_MALLOC, 1);
	return (root_paths);
}

char	*add_path2(char **exec_line, char **root_paths,	char *cmd_temp)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
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
		if (access(exec_line[0], F_OK) == 0)
		{
			free(cmd_temp);
			return (NULL);
		}
		i++;
	}
	return (cmd_temp);
}

int	add_path(char **exec_line, char **root_paths)
{
	char	*cmd_temp;

	if (root_paths == NULL || exec_line[0] == NULL)
		return (0);
	if (is_builtin(exec_line[0]) >= 0 && is_builtin(exec_line[0]) < 6)
		return (0);
	if (access(exec_line[0], F_OK) == 0)
		return (0);
	if (ft_strncmp(exec_line[0], "./", 2) == 0)
		return (0);
	cmd_temp = ft_strdup(exec_line[0]);
	cmd_temp = add_path2(exec_line, root_paths, cmd_temp);
	if (cmd_temp == NULL)
		return (0);
	free(exec_line[0]);
	exec_line[0] = cmd_temp;
	return (0);
}

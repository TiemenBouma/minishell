/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:59:21 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/19 08:12:08 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_home(t_node **list, char ***exec_line)
{
	t_node	*curr_node;

	curr_node = ft_find_node_in_list(list, "HOME=");
	if (curr_node == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	free_double_str(*exec_line);
	*exec_line = malloc(sizeof(char *) * 3);
	(*exec_line)[2] = NULL;
	(*exec_line)[0] = ft_strdup("cd");
	(*exec_line)[1] = ft_strdup(curr_node->str + 5);
	return ((*exec_line)[1]);
}

int	switch_old_pwd(t_node **list, char **exec_line, t_node	**temp_node)
{
	if (ft_strncmp(exec_line[1], "-", 2) == 0)
	{
		*temp_node = ft_find_node_in_list(list, "OLDPWD=");
		if (*temp_node == NULL)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 25);
			return (1);
		}
		else
			ft_print_var_content(list, "OLDPWD=");
	}
	return (0);
}

int	ch_old_dir(t_node **list, char ***exec_line, t_node *temp_node, char *new_str)
{
	if (ft_strncmp((*exec_line)[1], "-", 2) == 0)
	{
		free((*exec_line)[1]);
		(*exec_line)[1] = ft_strdup(temp_node->str + 7);
	}
	ft_find_and_edit_node(list, "OLDPWD", new_str);
	free(new_str);
	if (chdir((*exec_line)[1]))
		return (perror_msg("minishell: cd", (*exec_line)[1], EXIT_CD));
	return (0);
}

char	*getcwd_make_pwd(char *var_name)
{
	char	*new_str;
	char	*cwd;

	cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
	cwd[PATH_MAX] = '\0';
	if (getcwd(cwd, MAXPATHLEN) == NULL)
	{
		perror_msg("pwd", NULL, EXIT_PWD);
		free (cwd);
		return (NULL);
	}
	new_str = ft_strjoin(var_name, cwd);
	free(cwd);
	return (new_str);
}

int	ft_cd(t_node **list, char ***exec_line)
{
	char	*new_str;
	t_node	*temp_node;

	temp_node = NULL;
	if ((*exec_line)[1] == NULL)
	{
		set_home(list, exec_line);
		if ((*exec_line)[1] == NULL)
			return (1);
	}
	if (switch_old_pwd(list, (*exec_line), &temp_node))
		return (1);
	new_str = getcwd_make_pwd("OLDPWD=");
	if (new_str == NULL)
		return (1);
	if (ch_old_dir(list, exec_line, temp_node, new_str))
		return (1);
	new_str = getcwd_make_pwd("PWD=");
	ft_find_and_edit_node(list, "PWD", new_str);
	free(new_str);
	return (0);
}

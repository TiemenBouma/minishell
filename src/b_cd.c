/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:59:21 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/02 17:26:24 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *set_home(t_node **list)
{
	t_node *curr_node;
	curr_node = ft_find_node_in_list(list, "HOME=");
	if (curr_node == NULL)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return(NULL);
	}
	
	return (curr_node->str + 5);
	
}

int ft_cd(t_node **list, char **exec_line)
{
	char	*cwd;
	char	*new_str;
	t_node	*temp_node;
	
	if (exec_line[1] == NULL)
	{
		exec_line[1] = set_home(list);
		if (exec_line[1] == NULL)
			return (1);
	}
	if (ft_strncmp(exec_line[1], "-", 2) == 0)
	{
		temp_node = ft_find_node_in_list(list, "OLDPWD=");
		if (temp_node == NULL)
		{
			write(2, "bash: cd: OLDPWD not set\n", 25);
			return (1);
		}
		else
			ft_print_var_content(list, "OLDPWD=");
	}
	cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
	cwd[PATH_MAX] = '\0';
	if (getcwd(cwd, MAXPATHLEN) == NULL)
		return (perror_msg("pwd", NULL, EXIT_PWD));
	new_str = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	if (ft_strncmp(exec_line[1], "-", 2) == 0)
	{
		free(exec_line[1]);
		exec_line[1] = ft_strdup(temp_node->str + 7);
	}
	ft_find_and_edit_node(list, "OLDPWD", new_str);
	if (chdir(exec_line[1]))
		return (perror_msg("cd", exec_line[1], EXIT_CD));
	cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
	cwd[PATH_MAX] = '\0';
	if (getcwd(cwd, MAXPATHLEN) == NULL)
		return (perror_msg("pwd", NULL, EXIT_PWD));
	new_str = ft_strjoin("PWD=", cwd);
	ft_find_and_edit_node(list, "PWD", new_str);
	free(cwd);
	return (0);
}

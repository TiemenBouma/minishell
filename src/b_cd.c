/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:59:21 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/25 08:59:46 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_cd(t_node **list, char **exec_line)// WORKS WITH ABSOLUTE PATH, not relative. NEED TO BUILD IN CHECKS IF  getcwd AND chdir WORKED.
{
	char	*cwd;
	char	*new_str;
	
	if (exec_line[1] == NULL)
		return (0);
	if (ft_strncmp(exec_line[1], "-", ft_strlen(exec_line[1] + 1)) == 0)
	{
		if (find_var_in_list(list, "OLDPWD=") != NULL)
			ft_print_var_content(list, "OLDPWD=");
		else
			write(2, "bash: cd: OLDPWD not set\n", 25);
		return (0);
	}
	cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
	cwd[PATH_MAX] = '\0';
	if (getcwd(cwd, MAXPATHLEN) == NULL)
		return (perror_msg("pwd", NULL, EXIT_PWD));
	new_str = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
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

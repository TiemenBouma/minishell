/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:09:35 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/22 13:37:30 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_exit(char **s)
{
	int exit_code;

	exit_code = 0;
	if (s[1])
		exit_code = ft_atoi(s[1]);
	exit(exit_code % 255);
}

void	ft_echo(char **s)
{
	int	i = 1;
	int	nl;

	i = 1;
	nl = 1; 
	if (ft_strncmp(s[i], "-n",  1 + ft_strlen(s[i])) == 0)
	{
		nl = 0;
		i = 2;
	}
	while (s[i])
	{
		ft_putstr_fd(s[i], 1);
		if (nl == 1)
			write(1, " ", 2);
		i++;
	}
	if (nl == 1)
		ft_putstr_fd("\n", 1);

}

void	ft_pwd(t_node **list)
{
	ft_print_var_content(list, "PWD=");
}


int ft_cd(t_node **list, char **exec_line)// WORKS WITH ABSOLUTE PATH, not relative. NEED TO BUILD IN CHECKS IF  getcwd AND chdir WORKED.
{
	char	*cwd;
	char	*new_str;
	
	if (ft_strncmp(exec_line[1], "-", ft_strlen(exec_line[1] + 1) == 0))
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

void	ft_env(t_node **list)
{

	t_node *current;

	current = *list;
	while (1)
	{
		write(1, current->str, ft_strlen(current->str));
		write(1, "\n", 1);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
}

char	*make_var_name(char *var_line)
{
	char	*var_name;
	int		i;

	i = 0;
	while (var_line[i] && var_line[i] != '=')
	{
		i++;
	}
	var_name = ft_substr(var_line, 0, i);
	//malloc proctection
	return(var_name);
}

void	ft_unset(t_node **list, /*struct	s_main	*main_struct,*/ char *var_line)
{
	t_node	*match_node;
	char	*var_name;

	var_name = make_var_name(var_line);
	match_node = ft_find_node_in_list(list, var_name);
	free(var_name);
	if (match_node)
		ft_remove_node(list, match_node);
}

void	print_export(t_node **list)
{
	t_node *current;

	current = *list;
	while (1)
	{
		write(1, "declare -x ", 12);
		write(1, current->str, ft_strlen(current->str));
		write(1, "\n", 1);
		if (current->n == NULL)
			break ;
		current = current->n;
	}
}

void	ft_export(t_node **list, /*struct	s_main	*main_struct,*/ char *var_line)
{
	t_node	*new_node;
	t_node	*match_node;
	char	*var_name;

	if (!var_line)
		print_export(list);
	else 
	{
		var_name = make_var_name(var_line);
		match_node = ft_find_node_in_list(list, var_name);
		free(var_name);
		if (!match_node)
		{
			new_node = ft_new_node(var_line);
			ft_list_node_add_back(list, new_node);	
		}
		else
		{
			replace_node_content(match_node, var_line);
		}
		
	}
}

int	is_builtin(char	*s)
{
	// write(1, "Y1!\n", 4);
	if (!s)
		return (11);
	else if (ft_strncmp(s, "/usr/bin/cd", 11 + 1) == 0) //change abs path? exec all fucns with abs path?
		return (CD_BUILD);
	else if (ft_strncmp(s, "export", 6 + 1) == 0)
		return (EXPORT_BUILD);
	else if (ft_strncmp(s, "unset", 5 + 1) == 0)
		return (UNSET_BUILD);
	else if (ft_strncmp(s, "/bin/echo", 9 + 1) == 0)
		return (ECHO_BUILD);
	else if (ft_strncmp(s, "/bin/pwd", 8 + 1) == 0) //exec all fucns with abs path?
		return (PWD_BUILD);
	else if (ft_strncmp(s, "env", 3 + 1) == 0)
		return (ENV_BUILD);
	else if (ft_strncmp(s, "exit", 4 + 1) == 0)
		return (EXIT_BUILD);
	return (10);
}

int	exec_builtin(struct	s_cmd_info	*cmd_struct, int build_n)
{
	//char *cmd = s[0];

	// s[0] = "Yo";
	//printf ("test%s\n", cmd);
	//(void) exec_line;
	if (build_n == CD_BUILD) //change abs path? exec all fucns with abs path?
		return (ft_cd(&cmd_struct->env_llist, cmd_struct->exec.exec_line));
	else if (build_n == EXPORT_BUILD)
		ft_export(&cmd_struct->env_llist, cmd_struct->exec.exec_line[1]);
	else if (build_n == UNSET_BUILD)
		ft_unset(&cmd_struct->env_llist, cmd_struct->exec.exec_line[1]);
	else if (build_n == ECHO_BUILD)
		ft_echo(cmd_struct->exec.exec_line);
	else if (build_n == PWD_BUILD)
		ft_pwd(&cmd_struct->env_llist);
	else if (build_n == ENV_BUILD)
		ft_env(&cmd_struct->env_llist);
	else if (build_n == EXIT_BUILD)
		ft_exit(cmd_struct->exec.exec_line);
	return (0);
}


int	check_buildin_fork(struct s_cmd_info *cmd_struct)// NEED TO CHECK FOR SYSTEMFUNC probably
{
	int checker;
	
	checker = is_builtin(cmd_struct->exec.exec_line[0]);
	if (checker == CD_BUILD || checker == EXPORT_BUILD || checker == UNSET_BUILD)
		return (0);
	else
		return (1);
}

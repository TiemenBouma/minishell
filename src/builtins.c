/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:09:35 by dkocob        #+#    #+#                 */
/*   Updated: 2022/07/27 21:58:09 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *s)
{
	int	i = 0;
	// int	size_of_arg;
	// char *result;
	// s = "Yo";

	// write(1, "YO!\n", 4);
	// size_of_arg = 0;
	// size_of_arg += 7;
	while (s[i])
		i++;
	write (1, s, i);
}

// void	ft_pwd(struct	s_cmd_lines	*d)
// {
// 	//print current pwd
// }

// void	ft_cd(struct	s_cmd_lines	*d)
// {
// 	//check pwd
// 	//check if dest location is exist (access?)
// 	//modify pwd
// }

// void	ft_unset(struct	s_cmd_lines	*d, char *s)
// {
// 	// go to right position in d->env_list
// 	// delete existing node
// }

// void	ft_env(struct	s_cmd_lines	*d)
// {

// 	// while (d->env_list)
// 	//print current node
// 	//go to next node


// }

// void	ft_export(struct	s_cmd_lines	*d, char *s)
// {

// 	// go to right position in d->env_list
// 	//put new node 
// 	// or modify existing
// }

int	is_builtin(char	*s)
{
	// write(1, "Y1!\n", 4);
	if (!s)
		return (-1);
	if (ft_strncmp(s, "/bin/echo", 9 + 1) == 0)
		return (1);
	else if (ft_strncmp(s, "/usr/bin/cd", 11 + 1) == 0) //change abs path? exec all fucns with abs path?
		return (2);
	else if (ft_strncmp(s, "/bin/pwd", 8 + 1) == 0) //exec all fucns with abs path?
		return (3);
	else if (ft_strncmp(s, "export", 6 + 1) == 0)
		return (4);
	else if (ft_strncmp(s, "unset", 5 + 1) == 0)
		return (5);
	else if (ft_strncmp(s, "env", 3 + 1) == 0)
		return (6);
	else if (ft_strncmp(s, "exit", 4 + 1) == 0)
		exit (0);
	return (0);
}

int	exec_builtin(struct	s_cmd_lines	*d, char **s, int n)
{
	char *cmd = s[0];

	// s[0] = "Yo";
	printf ("%s\n", cmd);

	if (n == 1)
		ft_echo(d->cmd_info->pipe_cmd.exec_line[1]);
	// else if (n == 2) //change abs path? exec all fucns with abs path?
	// 	ft_cd(d);
	// else if (n == 2) //exec all fucns with abs path?
	// 	ft_pwd(d);
	// else if (n == 3)
	// 	ft_export(d, cmd);
	// else if (n == 4)
	// 	ft_unset(d, cmd);
	// else if (n == 5)
	// 	ft_env(d);
	exit (0);
}

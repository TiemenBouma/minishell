/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:09:35 by dkocob        #+#    #+#                 */
/*   Updated: 2022/07/27 17:49:33 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(struct	s_cmd_lines	*d)
{
	// int	i;
	int	size_of_arg;
	// char *result;

	size_of_arg = 0;
	size_of_arg += 7;
	while (d->cmd_info->pipe_cmd.exec_line[1][size_of_arg])
	{
		size_of_arg++;
	}
	write (1, &d->cmd_info->pipe_cmd.exec_line[1], size_of_arg);
}

void	ft_pwd(struct	s_cmd_lines	*d)
{
	// int	i;
	int	size_of_arg;
	// char *result;

	size_of_arg = 0;
	size_of_arg += 7;
	while (d->cmd_info->pipe_cmd.exec_line[1][size_of_arg])
	{
		size_of_arg++;
	}
	write (1, &d->cmd_info->pipe_cmd.exec_line[1], size_of_arg);
}

// void	ft_unset(struct	s_cmd_lines	*d)
// {
// 	// int	i;
// 	int	size_of_arg;
// 	// char *result;

// 	size_of_arg = 0;
// 	size_of_arg += 7;

// 	unset (&d->cmd_info->pipe_cmd.exec_line[1]);
// }

void	ft_env(struct	s_cmd_lines	*d)
{
	int	i;

	// while (d->)
	// size_of_arg = 0;
	// size_of_arg += 7;

	unset (&d->cmd_info->pipe_cmd.exec_line[1]);
}

int	builtins_handling(char	*s, int n)
{
	int i = 0;

	if (!s)
		return (NULL);
	if (ft_strncmp(s, "echo", 4 + 1) == 0)
		return (1);
	else if (ft_strncmp(s, "cd", 2 + 1) == 0)
		return (2);
	else if (ft_strncmp(s, "pwd", 3 + 1) == 0)
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
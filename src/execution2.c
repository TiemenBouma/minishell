/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:06:01 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/10 09:59:44 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child(struct s_main *vars, char **envp)
{
	dup2(vars->tube[1], STDOUT_FILENO);
	close(vars->tube[0]);
	vars->cmd_struct_arr[vars->curr_exec_cmd_n].exec.exec_line
	//p->cmd = ft_split(p->argv[vars->curr_exec_cmd_n + 1], ' ');
	if (p->cmd == NULL)
		error_msg(ERR_MALLOC, 1);
	p->cmd_path = find_cmd_path(p->root_paths, p->cmd[0]);
	if (execve(p->cmd_path, vars->cmd_struct_arr[vars->curr_exec_cmd_n].exec.exec_line, envp) < 0)
		error_msg(ERR_EXEC, 1);
}

void	fork_child(struct s_main *vars, char **envp)
{
	vars->curr_exec_cmd_n++;
	if (vars->pid_child > 0)
		vars->pid_child = fork();
	if (vars->pid_child < 0)
		error_msg(ERR_FORK, 1);
	if (vars->pid_child == 0)
		child(vars, envp);
}


void	parent_procces(struct s_main *vars, char **envp)
{
	int	status;
	int	exit_status;
	int	child_n;

	vars->curr_exec_cmd_n = 0;
	vars->pid_child = 1;
	while (vars->curr_exec_cmd_n < vars->cmd_count)
	{
		pipe(vars->tube);
		fork_child(vars, envp);
		if (vars->pid_child != 0)
		{
			dup2(vars->tube[0], STDIN_FILENO);
			close(vars->tube[1]);
		}
	}
	fork_child(vars, envp);
	waitpid(vars->pid_child, &status, 0);
	if (WIFEXITED(status) > 0)
	{
		exit_status = WEXITSTATUS(status);
		exit(exit_status);
	}
}
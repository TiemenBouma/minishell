/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/09/08 14:33:06 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;

static void	execve_error(char *path, int error, char *envpath)
{
	if (ft_strncmp(path, "./", 2) == 0 || envpath == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (error == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": execve error\n", 2);
	}
	exit (127);
}

static void	ft_execution_in_child(struct s_main *m_s, struct s_cmd_info *curr_cmd)
{
	if (is_builtin(curr_cmd->exec.exec_line[0]) < 7 && curr_cmd->set_file_err == 0)
		exit(exec_builtin(m_s, curr_cmd, is_builtin(curr_cmd->exec.exec_line[0])));
	else if (curr_cmd->set_file_err == 0)
	{
		curr_cmd->arr_env_list = make_arr_from_list(&m_s->env_llist);
		if (execve(curr_cmd->exec.exec_line[0], curr_cmd->exec.exec_line, curr_cmd->arr_env_list) == -1)
		{
			if (curr_cmd->exec.exec_line[0] == NULL)
				exit(0);
			execve_error(curr_cmd->exec.exec_line[0], errno, find_var_in_list(&m_s->env_llist, "PATH"));
		}
	}
	else
		exit(126);
}

static void	ft_redirections(struct s_main *m_s, int (*p)[2][2], int i, int id, struct s_cmd_info *curr_cmd)
{
	if ((id == 0 && check_buildin_fork(curr_cmd) == 1) || (id == 0 && m_s->cmd_count > 1))
	{
		if (curr_cmd->has_heredoc == 2)
		{
			err_chk(dup2(g_pipe_heredoc[curr_cmd->cmd_index + 1][P_OUT], S_IN), 2, "");
			close (g_pipe_heredoc[curr_cmd->cmd_index + 1][P_OUT]);
		}
		else if (curr_cmd->has_infile == 2 || i == 1)
			err_chk(dup2(curr_cmd->exec.fd_in, S_IN), 2, "");
		else
			err_chk(dup2((*p)[PREV][P_OUT], S_IN), 2, "");
		if (curr_cmd->exec.fd_out == 1 && m_s->cmd_count != i)
			err_chk(dup2((*p)[CUR][P_IN], S_OUT), 2, "");
		else
			err_chk(dup2(curr_cmd->exec.fd_out, S_OUT), 2, "");
		close ((*p)[CUR][P_OUT]);
		close ((*p)[PREV][P_IN]);
		ft_execution_in_child(m_s, curr_cmd);
	}
	close ((*p)[PREV][P_OUT]);
	close ((*p)[CUR][P_IN]);
	if (i == 1 || curr_cmd->has_heredoc == 2)
		close ((*p)[PREV][P_IN]);
	if (curr_cmd->has_heredoc == 2 && id != 0)
		close (g_pipe_heredoc[curr_cmd->cmd_index + 1][P_OUT]);
}

int	exec(struct	s_main *m_s)
{
	int					i = 0;
	int					build_return;
	int					id = 1;
	int					p[2][2];

	build_return = -1;
	err_chk(pipe(p[CUR]), 1, "");
	while (i < m_s->cmd_count)
	{
		i++;
		err_chk(pipe(p[CUR]), 1, "");
		if (&m_s->c_s_arr[i - 1].exec.exec_line[0] && is_builtin(m_s->c_s_arr[i - 1].exec.exec_line[0]) == EXIT_BUILD && m_s->cmd_count == 1)
		{
			build_return = ft_exit(m_s->c_s_arr[i - 1].exec.exec_line, 0, m_s);
			continue ;
		}
		if (check_buildin_fork(&m_s->c_s_arr[i - 1]) == 0 && m_s->c_s_arr[i - 1].set_file_err == 0 && m_s->cmd_count == 1)
		{
			build_return = exec_builtin(m_s, &m_s->c_s_arr[i - 1], is_builtin(m_s->c_s_arr[i - 1].exec.exec_line[0]));
			continue ;
		}
		signal(SIGINT, sigint_handler_in_process);
		signal(SIGQUIT, sigquit_handler_in_process);
		if (check_buildin_fork(&m_s->c_s_arr[i - 1]) == 1 || m_s->cmd_count > 1)
			id = fork();
		err_chk(id, 1, "");
		ft_redirections(m_s, &p, i, id, &m_s->c_s_arr[i - 1]);
	}
	close (p[CUR][P_OUT]);
	close (p[PREV][P_IN]);
	waitpid(id, &i, 0);
	while (wait(NULL) != -1)
		;
	signals_handeler();
	if (build_return >= 0)
	{
		return (build_return);
	}
	return (WEXITSTATUS(i));
}

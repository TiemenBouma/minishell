/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:53:02 by dkocob        #+#    #+#                 */
/*   Updated: 2022/09/25 10:23:16 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;
void	execve_error(char *path, int error, char *envpath);

static void	ft_exec_in_child(struct s_main *m_s, struct s_cmd_info *curr_cmd)
{
	if (is_builtin(curr_cmd->exec_line[0]) < 7 && curr_cmd->set_file_err == 0)
		exit(exec_builtin(m_s, curr_cmd, is_builtin(curr_cmd->exec_line[0])));
	else if (curr_cmd->set_file_err == 0)
	{
		curr_cmd->e_list = make_arr_from_list(&m_s->env_llist);
		if (execve(curr_cmd->exec_line[0],
				curr_cmd->exec_line, curr_cmd->e_list) == -1)
		{
			if (curr_cmd->exec_line[0] == NULL)
				exit(0);
			execve_error(curr_cmd->exec_line[0],
				errno, find_var_in_list(&m_s->env_llist, "PATH"));
		}
	}
	else
		exit(126);
}

static void	ft_redirections(struct s_main *m_s,
	int (*p)[2][2], int i, int id, struct s_cmd_info *curr_cmd)
{
	if ((id == 0 && check_buildin_fork(curr_cmd) == 1)
		|| (id == 0 && m_s->cmd_count > 1))
	{
		if (curr_cmd->has_heredoc == 2)
		{
			err_chk(dup2(g_pipe_heredoc[curr_cmd->cmd_index + 1][P_OUT],
					S_IN), 2, "");
			close (g_pipe_heredoc[curr_cmd->cmd_index + 1][P_OUT]);
		}
		else if (curr_cmd->has_infile == 2 || i == 1)
			err_chk(dup2(curr_cmd->fd_in, S_IN), 2, "");
		else
			err_chk(dup2((*p)[i % 2][P_OUT], S_IN), 2, "");
		if (curr_cmd->fd_out == 1 && m_s->cmd_count != i)
			err_chk(dup2((*p)[(i + 1) % 2][P_IN], S_OUT), 2, "");
		else
			err_chk(dup2(curr_cmd->fd_out, S_OUT), 2, "");
		close ((*p)[(i + 1) % 2][P_OUT]);
		close ((*p)[i % 2][P_IN]);
		ft_exec_in_child(m_s, curr_cmd);
	}
}

void	sig_exec(struct s_cmd_info *curr_cmd)
{
	if (curr_cmd->exec_line[0] != NULL)
	{
		if (ft_strcmp("./minishell", curr_cmd->exec_line[0]) == 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			return ;
		}
	}
	signal(SIGINT, sigint_handler_in_process);
	signal(SIGQUIT, sigquit_handler_in_process);
}

static int	ft_iterations(struct s_main *m_s,
	int (*p)[2][2], int i, int *id, struct s_cmd_info *curr_cmd)
{
	err_chk(pipe((*p)[(i + 1) % 2]), 1, "");
	if (curr_cmd->exec_line[0] && is_builtin(curr_cmd->exec_line[0])
		== EXIT_BUILD && m_s->cmd_count == 1)
		return (ft_exit(m_s->c_s_arr[i - 1].exec_line, 0, m_s));
	if (check_buildin_fork(curr_cmd) == 0 && curr_cmd->set_file_err
		== 0 && m_s->cmd_count == 1)
		return (exec_builtin(m_s, curr_cmd,
				is_builtin(curr_cmd->exec_line[0])));
	sig_exec(curr_cmd);
	if (check_buildin_fork(&m_s->c_s_arr[i - 1]) == 1 || m_s->cmd_count > 1)
		*id = fork();
	err_chk(*id, 1, "");
	ft_redirections(m_s, p, i, *id, curr_cmd);
	close ((*p)[i % 2][P_OUT]);
	close ((*p)[(i + 1) % 2][P_IN]);
	if (i == 1 || curr_cmd->has_heredoc == 2)
		close ((*p)[i % 2][P_IN]);
	if (curr_cmd->has_heredoc == 2 && id != 0)
		close (g_pipe_heredoc[curr_cmd->cmd_index + 1][P_OUT]);
	return (-1);
}

int	exec(struct	s_main *m_s)
{
	int					i;
	int					build_return;
	int					id;
	int					p[2][2];

	i = 0;
	id = 1;
	build_return = -1;
	err_chk(pipe(p[(i + 1) % 2]), 1, "");
	while (i < m_s->cmd_count)
	{
		i++;
		build_return = ft_iterations(m_s, &p, i, &id, &m_s->c_s_arr[i - 1]);
	}
	close (p[(i + 1) % 2][P_OUT]);
	close (p[i % 2][P_IN]);
	waitpid(id, &i, 0);
	while (wait(NULL) != -1)
		;
	signals_handeler();
	if (build_return >= 0)
		return (build_return);
	return (WEXITSTATUS(i));
}

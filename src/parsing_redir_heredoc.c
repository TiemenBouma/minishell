/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:12:10 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 13:42:55 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;

void	exec_heredoc(struct s_main *m_s, struct s_cmd_info *cmd_struct,
	int curr_heredoc, int i)
{
	int	total_heredoc;

	total_heredoc = heredoc_counter(cmd_struct->curr_line_tokens);
	if (total_heredoc > curr_heredoc)
	{
		dummy_heredoc(cmd_struct->curr_line_tokens[i + 1]);
		exit(0);
	}
	if (total_heredoc == curr_heredoc)
	{
		close(g_pipe_heredoc[cmd_struct->cmd_index + 1][P_OUT]);
		heredoc(m_s, cmd_struct->curr_line_tokens[i + 1],
			cmd_struct->cmd_index);
		exit(0);
	}
}

int	check_sig_exit(struct s_cmd_info *cmd_struct, int id)
{
	int	status;

	waitpid(id, &status, 0);
	if (WEXITSTATUS(status) == 10)
	{
		cmd_struct->set_file_err = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		signal(SIGINT, sigint_handler);
		return (1);
	}
	return (0);
}

int	fork_heredoc(struct s_main *m_s, struct s_cmd_info *cmd_struct,
	int curr_heredoc, int i)
{
	int	id;

	id = fork();
	if (id == 0)
		exec_heredoc(m_s, cmd_struct, curr_heredoc, i);
	if (heredoc_counter(cmd_struct->curr_line_tokens) == curr_heredoc)
		close(g_pipe_heredoc[cmd_struct->cmd_index + 1][P_IN]);
	if (check_sig_exit(cmd_struct, id))
		return (1);
	return (0);
}

int	heredoc_redir_check(struct s_main *m_s, struct s_cmd_info *cmd_struct)
{
	int	i;
	int	curr_heredoc;

	i = 0;
	curr_heredoc = 0;
	while (i < cmd_struct->token_count)
	{
		if (is_arrow_sign(cmd_struct->curr_line_tokens[i]) == HEREDOC)
		{
			if (cmd_struct->curr_line_tokens[i + 1] == NULL
				|| is_special_c_redir(cmd_struct->curr_line_tokens[i + 1]))
				return (1);
			curr_heredoc++;
			signal(SIGINT, SIG_IGN);
			if (heredoc_counter(cmd_struct->curr_line_tokens) == curr_heredoc)
				err_chk(pipe(g_pipe_heredoc[cmd_struct->cmd_index + 1]), 1, "");
			if (fork_heredoc(m_s, cmd_struct, curr_heredoc, i))
				break ;
			signals_handeler();
		}
		i++;
	}
	return (0);
}

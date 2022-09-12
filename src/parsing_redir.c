/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:30:01 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/12 14:54:06 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;

int	redir_check(struct s_cmd_info *cmd_struct)
{
	int		i;
	int		curr_heredoc;
	char	*token;
	char	*n_token;

	i = 0;
	curr_heredoc = 0;
	while (i < cmd_struct->token_count)
	{
		token = cmd_struct->curr_line_tokens[i];
		n_token = cmd_struct->curr_line_tokens[i + 1];
		if (is_arrow_sign(token) == HEREDOC)
		{
			if (cmd_struct->curr_line_tokens[i + 1] == NULL || is_special_c_redir(cmd_struct->curr_line_tokens[i + 1]))
			{
				set_redir_error(cmd_struct, cmd_struct->curr_line_tokens[i + 1]);
				return (1);
			}
			curr_heredoc++;
			cmd_struct->has_heredoc = 2;
			if (cmd_struct->has_infile == 2)
			{
				if (cmd_struct->fd_in >= 0)
				{
					close(cmd_struct->fd_in);
				}
				cmd_struct->has_infile = 1;
			}
		}
		if (is_arrow_sign(token) == SMALLER)
		{
			if (cmd_struct->infile)
				free(cmd_struct->infile);
			if (cmd_struct->has_heredoc == 2)
				cmd_struct->has_heredoc = 1;
			cmd_struct->has_infile = 2;
			if (n_token == NULL || is_special_c_redir(n_token))
			{
				set_redir_error(cmd_struct, n_token);
				return (1);
			}
			cmd_struct->infile = ft_strdup(n_token);
			if (open_fd_in(cmd_struct) == -1)
				return (-1);
		}
		if (is_arrow_sign(token) == GREATER)
		{
			if (cmd_struct->has_outfile >= 1)
				free(cmd_struct->outfile);
			cmd_struct->has_outfile++;
			if (n_token == NULL || is_special_c_redir(n_token))
			{
				set_redir_error(cmd_struct, n_token);
				return (1);
			}
			cmd_struct->outfile = ft_strdup(n_token);
			if (open_fd_out(cmd_struct) == -1)
				return (-1);
		}
		if (is_arrow_sign(token) == APPEND)
		{
			if (cmd_struct->has_appendfile >= 1)
				free(cmd_struct->appendfile);
			cmd_struct->has_appendfile++;
			if (n_token == NULL || is_special_c_redir(n_token))
			{
				set_redir_error(cmd_struct, n_token);
				return (1);
			}
			cmd_struct->appendfile = ft_strdup(n_token);
			if (open_fd_out_append(cmd_struct) == -1)
				return (-1);
		}
		i++;
	}
	if (cmd_struct->has_heredoc == 2 && cmd_struct->fd_in != 0)
		close(cmd_struct->fd_in);
	if (cmd_struct->has_infile == 2 && cmd_struct->has_heredoc > 0)
		close(cmd_struct->heredoc_pipe[0]);
	return (1);
}

int	heredoc_redir_check(struct s_cmd_info *cmd_struct)
{
	int	i;
	int	total_heredoc;
	int	curr_heredoc;
	int	id;
	int	status;

	i = 0;
	curr_heredoc = 0;
	total_heredoc = heredoc_counter(cmd_struct->curr_line_tokens);
	while (i < cmd_struct->token_count)
	{
		if (is_arrow_sign(cmd_struct->curr_line_tokens[i]) == HEREDOC)
		{
			if (cmd_struct->curr_line_tokens[i + 1] == NULL || is_special_c_redir(cmd_struct->curr_line_tokens[i + 1]))
				return (1);
			curr_heredoc++;
			signal(SIGINT, SIG_IGN);
			if (total_heredoc == curr_heredoc)
				err_chk(pipe(g_pipe_heredoc[cmd_struct->cmd_index + 1]), 1, "");
			id = fork();
			if (id == 0)
			{
				if (total_heredoc > curr_heredoc)
				{
					dummy_heredoc(cmd_struct->curr_line_tokens[i + 1]);
					exit(0);
				}
				if (total_heredoc == curr_heredoc)
				{
					close(g_pipe_heredoc[cmd_struct->cmd_index + 1][P_OUT]);
					heredoc(cmd_struct->curr_line_tokens[i + 1], cmd_struct->cmd_index);
					exit(0);
				}
			}
			if (total_heredoc == curr_heredoc)
				close(g_pipe_heredoc[cmd_struct->cmd_index + 1][P_IN]);
			waitpid(id, &status, 0);
			if (WEXITSTATUS(status) == 10)
			{
				cmd_struct->set_file_err = 1;
				write(1, "\n", 1);
				rl_on_new_line();
				rl_replace_line("", 0);
				signal(SIGINT, sigint_handler);
				break ;
			}
			signal(SIGINT, sigint_handler);
		}
		i++;
	}
	return (0);
}
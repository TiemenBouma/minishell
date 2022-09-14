/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:30:01 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 14:11:09 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_heredoc(struct s_cmd_info *cmd_struct,
	char *token, char *n_token, int *curr_heredoc)
{
	if (is_arrow_sign(token) == HEREDOC)
	{
		if (n_token == NULL
			|| is_special_c_redir(n_token))
		{
			set_redir_error(cmd_struct, n_token);
			return (1);
		}
		(*curr_heredoc)++;
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
	return (0);
}

int	is_smaller(struct s_cmd_info *cmd_struct,
	char *token, char *n_token)
{
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
	return (0);
}

int	is_greater(struct s_cmd_info *cmd_struct,
	char *token, char *n_token)
{
	if (is_arrow_sign(token) == GREATER)
	{
		if (n_token == NULL || is_special_c_redir(n_token))
		{
			set_redir_error(cmd_struct, n_token);
			return (1);
		}
		if (cmd_struct->has_outfile >= 1)
			free(cmd_struct->outfile);
		cmd_struct->has_outfile++;
		cmd_struct->outfile = ft_strdup(n_token);
		if (open_fd_out(cmd_struct) == -1)
			return (-1);
	}
	return (0);
}

int	is_append(struct s_cmd_info *cmd_struct,
	char *token, char *n_token)
{
	if (is_arrow_sign(token) == APPEND)
	{
		if (cmd_struct->has_appendfile >= 1)
			free(cmd_struct->appendfile);
		if (n_token == NULL || is_special_c_redir(n_token))
		{
			set_redir_error(cmd_struct, n_token);
			return (1);
		}
		cmd_struct->has_appendfile++;
		cmd_struct->appendfile = ft_strdup(n_token);
		if (open_fd_out_append(cmd_struct) == -1)
			return (-1);
	}
	return (0);
}

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
		if (is_heredoc(cmd_struct, token, n_token, &curr_heredoc))
			return (1);
		if (is_smaller(cmd_struct, token, n_token))
			return (1);
		if (is_greater(cmd_struct, token, n_token))
			return (1);
		if (is_append(cmd_struct, token, n_token))
			return (1);
		i++;
	}
	if (cmd_struct->has_heredoc == 2 && cmd_struct->fd_in != 0)
		close(cmd_struct->fd_in);
	if (cmd_struct->has_infile == 2 && cmd_struct->has_heredoc > 0)
		close(cmd_struct->heredoc_pipe[0]);
	return (1);
}

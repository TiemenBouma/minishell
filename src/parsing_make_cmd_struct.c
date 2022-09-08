/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_make_cmd_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:48:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/08 11:51:32 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;

static int	copy_token(char **src_str, char **dest_str, int count)//m_s->cmd_lines[line], m_s->c_s_arr[line].tokens);
{
	int i;

	i = 0;
	while (i < count)
	{
		dest_str[i] = ft_strdup(src_str[i]);
		//malloc protect
		i++;
	}
	return (0);
}

void	set_err(struct s_cmd_info *cmd_struct)
{
	//cmd_struct->set_file_err = 1;
	cmd_struct->has_infile = 0;
	cmd_struct->has_outfile = 0;
	cmd_struct->has_appendfile = 0;
	cmd_struct->has_heredoc = 0;
	//close(S_IN);//cmd_struct->exec.fd_in = S_IN;
	cmd_struct->exec.fd_out = S_OUT;
	//cmd_struct->exec.exec_line[0] = NULL;
}

void	init_cmd_struct(struct s_main *m_s, struct s_cmd_info *cmd_struct, int line)
{
	cmd_struct->cmd_index = line;
	cmd_struct->exec.cmd_count = m_s->cmd_count;
	cmd_struct->has_infile = 0;
	cmd_struct->has_outfile = 0;
	cmd_struct->has_appendfile = 0;
	cmd_struct->exec.fd_out = 1;
	cmd_struct->exec.fd_in = 0;
	cmd_struct->has_heredoc = 0;
	cmd_struct->heredoc_fd_opened = 0;
	cmd_struct->heredoc_filename = NULL;
	cmd_struct->infile = NULL;
	cmd_struct->outfile = NULL;
	cmd_struct->env_llist = m_s->env_llist;
	cmd_struct->pid_child = 1;
	cmd_struct->exec.heredoc = NULL;
	cmd_struct->arr_env_list = NULL;
	cmd_struct->err_syntax = 0;
	cmd_struct->set_file_err = 0;
}

void	redir_execline_path(struct s_main *m_s)
{
	int	line;

	line = 0;
	while (line < m_s->cmd_count)
	{
		redir_check(&m_s->c_s_arr[line]);
		make_exec_line(&m_s->c_s_arr[line]);
		add_path(m_s->c_s_arr[line].exec.exec_line, m_s->root_paths);
		line++;
	}
}

int	make_cmd_structs(struct s_main *m_s)
{
	int	line;
	int	cmd_line_count;

	line = 0;
	cmd_line_count = 0;
	while (m_s->cmd_lines[m_s->cmd_count])
		m_s->cmd_count++;
	m_s->c_s_arr = malloc(sizeof(struct s_cmd_info) * m_s->cmd_count);
	while (line < m_s->cmd_count)
	{
		cmd_line_count = 0;
		while (m_s->cmd_lines[line][cmd_line_count])
			cmd_line_count++;
		m_s->c_s_arr[line].token_count = cmd_line_count;
		m_s->c_s_arr[line].curr_line_tokens = malloc(sizeof(char *) * (cmd_line_count + 1));
		if (m_s->c_s_arr[line].curr_line_tokens == NULL)
			exit (1);//(ERR_MALLOC);
		m_s->c_s_arr[line].curr_line_tokens[cmd_line_count] = NULL;
		copy_token(m_s->cmd_lines[line], m_s->c_s_arr[line].curr_line_tokens, m_s->c_s_arr[line].token_count);
		init_cmd_struct(m_s, &m_s->c_s_arr[line], line);
		g_pipe_heredoc[0][0] = line;
		heredoc_redir_check(&m_s->c_s_arr[line]);
		line++;
	}
	redir_execline_path(m_s);
	return (1);
}

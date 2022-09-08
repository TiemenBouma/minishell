/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:10:25 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/08 11:51:32 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int **g_pipe_heredoc;

void	free_double_str(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_triple_str(char ***str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free_double_str(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_cmd_info(struct s_cmd_info *c_s_arr)
{
	free_double_str(c_s_arr->curr_line_tokens);
	if (c_s_arr->arr_env_list)
		free_double_str(c_s_arr->arr_env_list);
	// c_s_arr->token_count = 0;
	// c_s_arr->has_infile = 0;
	// c_s_arr->has_outfile = 0;
	free(c_s_arr->infile);
	free(c_s_arr->outfile);
	free_double_str(c_s_arr->exec.exec_line);
}

void free_global(struct s_main *m_s)
{
	int	i;

	i = 0;
	while (i < m_s->cmd_count + 1)
	{
		free(g_pipe_heredoc[i]);
		i++;
	}
	free(g_pipe_heredoc);
	g_pipe_heredoc = NULL;
}

void	free_struct(struct s_main *m_s)
{
	int i;

	i = 0;
	if (g_pipe_heredoc)
		free_global(m_s);
	free(m_s->input_str);
	//free_double_str(m_s->root_paths);
	if (m_s->all_tokens)
		free_double_str(m_s->all_tokens);
	m_s->all_tokens = NULL;
	if (m_s->cmd_lines)
	{
		free_triple_str(m_s->cmd_lines);
		m_s->cmd_lines = NULL;
	}
	if (m_s->root_paths != NULL)
	{
		free_double_str(m_s->root_paths);
		m_s->root_paths = NULL;
	}
	while (i < m_s->cmd_count)
	{
		free_cmd_info(&m_s->c_s_arr[i]);
		i++;
	}
	m_s->cmd_count = 0;
	if (m_s->c_s_arr)
	{
		free(m_s->c_s_arr);
		m_s->c_s_arr = NULL;
	}
	//m_s->curr_exec_cmd_n = 0;
}

//m_s->c_s_arr[line].curr_line_tokens 
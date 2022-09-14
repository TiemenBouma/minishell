/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:10:25 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 13:34:24 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;

void	free_double_str(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	if (str[0] == NULL)
	{
		free(str[0]);
		return ;
	}
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

void	free_cmd_info(struct s_cmd_info *c_s)
{
	free_double_str(c_s->curr_line_tokens);
	if (c_s->e_list)
		free_double_str(c_s->e_list);
	if (c_s->infile)
		free(c_s->infile);
	if (c_s->outfile)
		free(c_s->outfile);
	if (c_s->appendfile)
		free(c_s->appendfile);
	if (c_s->heredoc)
		free(c_s->heredoc);
	if (c_s->exec_line != NULL)
		free_double_str(c_s->exec_line);
}

void	free_global(struct s_main *m_s)
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
	int	i;

	i = 0;
	if (g_pipe_heredoc)
		free_global(m_s);
	free(m_s->input_str);
	if (m_s->all_tokens)
		free_double_str(m_s->all_tokens);
	m_s->all_tokens = NULL;
	if (m_s->cmd_lines)
		free_triple_str(m_s->cmd_lines);
	if (m_s->root_paths != NULL)
		free_double_str(m_s->root_paths);
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
}

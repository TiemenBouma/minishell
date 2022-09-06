/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:10:25 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/10 10:19:08 by tbouma           ###   ########.fr       */
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

void	free_cmd_info(struct s_cmd_info *cmd_struct_arr)
{
	free_double_str(cmd_struct_arr->curr_line_tokens);
	if (cmd_struct_arr->arr_env_list)
		free_double_str(cmd_struct_arr->arr_env_list);
	// cmd_struct_arr->token_count = 0;
	// cmd_struct_arr->has_infile = 0;
	// cmd_struct_arr->has_outfile = 0;
	free(cmd_struct_arr->infile);
	free(cmd_struct_arr->outfile);
	free_double_str(cmd_struct_arr->exec.exec_line);
}

void free_global(struct s_main *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->cmd_count + 1)
	{
		free(g_pipe_heredoc[i]);
		i++;
	}
	free(g_pipe_heredoc);
	g_pipe_heredoc = NULL;
}

void	free_struct(struct s_main *main_struct)
{
	int i;

	i = 0;
	if (g_pipe_heredoc)
		free_global(main_struct);
	free(main_struct->input_str);
	//free_double_str(main_struct->root_paths);
	if (main_struct->all_tokens)
		free_double_str(main_struct->all_tokens);
	main_struct->all_tokens = NULL;
	if (main_struct->cmd_lines)
	{
		free_triple_str(main_struct->cmd_lines);
		main_struct->cmd_lines = NULL;
	}
	if (main_struct->root_paths != NULL)
	{
		free_double_str(main_struct->root_paths);
		main_struct->root_paths = NULL;
	}
	while (i < main_struct->cmd_count)
	{
		free_cmd_info(&main_struct->cmd_struct_arr[i]);
		i++;
	}
	main_struct->cmd_count = 0;
	if (main_struct->cmd_struct_arr)
	{
		free(main_struct->cmd_struct_arr);
		main_struct->cmd_struct_arr = NULL;
	}
	//main_struct->curr_exec_cmd_n = 0;
}

//main_struct->cmd_struct_arr[line].curr_line_tokens 
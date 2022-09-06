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
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_triple_str(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free_double_str(str[i]);
		i++;
	}
	free(str);
}

void	free_cmd_info(struct s_cmd_info *cmd_struct_arr)
{
	free_double_str(cmd_struct_arr->curr_line_tokens);
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
	while (i < main_struct->cmd_count)
	{
		free(g_pipe_heredoc[i]);
		i++;
	}
	free(g_pipe_heredoc);
}

void	free_struct(struct s_main *main_struct)
{
	int i;

	i = 0;
	free_global(main_struct);
	free(main_struct->input_str);
	//free_double_str(main_struct->root_paths);
	free_double_str(main_struct->all_tokens);
	main_struct->all_tokens = NULL;
	free_triple_str(main_struct->cmd_lines);
	if (main_struct->root_paths != NULL)
		free_double_str(main_struct->root_paths);
	while (i < main_struct->cmd_count)
	{
		free_cmd_info(&main_struct->cmd_struct_arr[i]);
		i++;
	}
	main_struct->cmd_count = 0;
	free(main_struct->cmd_struct_arr);
	//main_struct->curr_exec_cmd_n = 0;
}

//main_struct->cmd_struct_arr[line].curr_line_tokens 
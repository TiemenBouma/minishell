/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:10:25 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/09 14:21:32 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_cmd_info(struct s_cmd_info *curr_cmd_info)
{
	free_double_str(curr_cmd_info->curr_line_tokens);
	curr_cmd_info->token_count = 0;
	curr_cmd_info->has_infile = 0;
	curr_cmd_info->has_outfile = 0;
	free(curr_cmd_info->infile);
	free(curr_cmd_info->outfile);
	free_double_str(curr_cmd_info->exec.exec_line);
}

void	free_struct(struct s_main *main_struct)
{
	int i;

	i = 0;
	free(main_struct->input_str);
	//free_double_str(main_struct->root_paths);
	free_double_str(main_struct->all_tokens);
	free_triple_str(main_struct->cmd_lines);
	if (main_struct->root_paths != NULL)
		free_double_str(main_struct->root_paths);
	main_struct->cmd_count = 0;
	while (i < main_struct->cmd_count)
	{
		free_cmd_info(&main_struct->curr_cmd_info[i]);
		i++;
	}
	//main_struct->curr_exec_cmd_n = 0;
}
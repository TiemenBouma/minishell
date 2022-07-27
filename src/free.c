/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:10:25 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/27 13:10:39 by tbouma           ###   ########.fr       */
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

void	free_cmd_info(struct s_cmd_info *cmd_info)
{
	free_double_str(cmd_info->tokens);
	cmd_info->token_count = 0;
	cmd_info->has_infile = 0;
	cmd_info->has_outfile = 0;
	free(cmd_info->infile);
	free(cmd_info->outfile);
	free_double_str(cmd_info->pipe_cmd.exec_line);
}

void	free_struct(struct s_cmd_lines *var)
{
	int i;

	i = 0;
	free(var->input_str);
	//free_double_str(var->root_paths);
	free_double_str(var->all_tokens);
	free_triple_str(var->cmd_lines);
	var->cmd_count = 0;
	while (i < var->cmd_count)
	{
		free_cmd_info(&var->cmd_info[i]);
		i++;
	}
	var->curr_exec_cmd_n = 0;
}
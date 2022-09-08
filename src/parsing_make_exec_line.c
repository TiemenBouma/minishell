/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_make_exec_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:43:44 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/08 13:43:09 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_exec_tokens(struct s_cmd_info *cmd_struct)
{
	int exec_token;
	int	token_n;
	//int value;

	token_n = 0;
	exec_token = 0;
	while (token_n < cmd_struct->token_count)
	{
		//value = is_arrow_sign(cmd_struct->curr_line_tokens[token_n]);
		if (!is_arrow_sign(cmd_struct->curr_line_tokens[token_n]))//(value != SMALLER && value != GREATER)//(cmd_struct->curr_line_tokens[token_n][0] != '<' && cmd_struct->curr_line_tokens[token_n][0] != '>')
		{
			cmd_struct->exec.exec_line[exec_token] = ft_strdup(cmd_struct->curr_line_tokens[token_n]);
			exec_token++;
		}
		else if (is_arrow_sign(cmd_struct->curr_line_tokens[token_n]))//(value == GREATER || value == SMALLER)//(cmd_struct->curr_line_tokens[token_n][0] == '<' || cmd_struct->curr_line_tokens[token_n][0] == '>')
		{
			if (cmd_struct->curr_line_tokens[token_n + 1] == NULL)
				return(-1);//(ERR_INPUT);
			else
				token_n++;
		}
		token_n++;
	}
	return (0);
}

static int	calc_exec_line_len(struct s_cmd_info *cmd_struct)
{
	int	i;
	int	exec_len;

	i = 0;
	exec_len = 0;
	while (i < cmd_struct->token_count)
	{
		if (!is_arrow_sign(cmd_struct->curr_line_tokens[i]))
		{
			if ((i != 0 && !is_arrow_sign(cmd_struct->curr_line_tokens[i - 1])) || i == 0)
				exec_len++;
		}
		i++;
	}
	return (exec_len);
}

int	make_exec_line(struct s_cmd_info *cmd_struct)
{
	int	exec_len;

	exec_len = 0;
	exec_len = calc_exec_line_len(cmd_struct);
	//printf("LEN = %d\n", exec_len);
	cmd_struct->exec.exec_line = malloc(sizeof(char *) * (exec_len + 1));
	//malloc protection
	cmd_struct->exec.exec_line[exec_len] = NULL;
	find_exec_tokens(cmd_struct);
	
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_make_exec_line.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 10:43:44 by tbouma        #+#    #+#                 */
/*   Updated: 2022/09/13 11:19:22 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_exec_tokens(struct s_cmd_info *cmd_struct)
{
	int	exec_token;
	int	token_n;

	token_n = 0;
	exec_token = 0;
	while (token_n < cmd_struct->token_count)
	{
		if (!is_arrow_sign(cmd_struct->curr_line_tokens[token_n]))
		{
			cmd_struct->exec_line[exec_token]
				= ft_strdup(cmd_struct->curr_line_tokens[token_n]);
			exec_token++;
		}
		else if (is_arrow_sign(cmd_struct->curr_line_tokens[token_n]))
		{
			if (cmd_struct->curr_line_tokens[token_n + 1] == NULL)
				return (-1);
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
			if ((i != 0 && !is_arrow_sign(
						cmd_struct->curr_line_tokens[i - 1])) || i == 0)
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
	cmd_struct->exec_line = malloc(sizeof(char *) * (exec_len + 1));
	if (cmd_struct->exec_line == NULL)
		exit(1);
	cmd_struct->exec_line[exec_len] = NULL;
	find_exec_tokens(cmd_struct);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:48:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/22 14:19:01 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	calc_exec_line_len(struct s_cmd_info *cmd_struct)
{
	int i;
	int	exec_len;

	i = 0;
	exec_len = 0;
	while (i < cmd_struct->token_count)
	{
		if (cmd_struct->tokens[i][0] != '<' && cmd_struct->tokens[i][0] != '>')
			exec_len++;
		else if (cmd_struct->tokens[i][0] == '<' || cmd_struct->tokens[i][0] == '>')
		{
			if (cmd_struct->tokens[i + 1] == NULL)
				return(ERR_INPUT);
			else
				i++;
		}
		i++;
	}
	return (exec_len);
}

static int	make_exec_line(struct s_cmd_info *cmd_struct)
{
	int i;
	int	exec_len;

	i = 0;
	exec_len = 0;
	exec_len = calc_exec_line_len(cmd_struct);
	cmd_struct->pipe_cmd.exec_line = malloc(sizeof(char *) * )
	
}

static int	make_pipe_cmd(struct s_cmd_info *cmd_struct)
{
	make_exec_line(cmd_struct);
	//open FD IN and FD_OUT
}

static int	redir_check(struct s_cmd_info *cmd_struct)
{
	int	i;

	i = 0;
	while (i < cmd_struct->token_count)
	{
		if (cmd_struct->tokens[i][0] == '<')
		{
			if (cmd_struct->has_redir_in == 1);
				free(cmd_struct->redir_in);
			cmd_struct->has_redir_in = 1;
			cmd_struct->redir_in = ft_strdup(cmd_struct->tokens[i]);
		}
		
		if (cmd_struct->tokens[i][0] == '>')
		{
			if (cmd_struct->has_redir_out == 1);
				free(cmd_struct->redir_out);
			cmd_struct->has_redir_out = 1;
			cmd_struct->redir_in = ft_strdup(cmd_struct->tokens[i]);
		}
		i++;
	}
}

static int	copy_token(char **src_str, char **dest_str, int count)//cmd_lines->cmd_lines[line], cmd_lines->cmd_info[line].tokens);
{
	int i;

	i = 0;
	while (i < count)
	{
		dest_str = ft_strdup(src_str[i]);
		//malloc protect
		i++;
	}
	return (0);
}

make_cmd_structs(struct s_cmd_lines *cmd_lines)
{
	int line;
	int	cmd_line_count;
	
	line = 0;
	cmd_line_count = 0;
	while (cmd_lines->cmd_lines[cmd_lines->cmd_count])
		cmd_lines->cmd_count++;
	cmd_lines->cmd_info = malloc(sizeof(struct s_cmd_info) * cmd_lines->cmd_count);
	while (line < cmd_lines->cmd_count)
	{
		cmd_lines->cmd_info[line].has_redir_in = 0;
		cmd_lines->cmd_info[line].has_redir_out = 0;
		cmd_line_count = 0;
		while (cmd_lines->cmd_lines[line][cmd_line_count])
			cmd_line_count++;
		cmd_lines->cmd_info[line].token_count = cmd_line_count;
		cmd_lines->cmd_info[line].tokens = malloc(sizeof(char *) * (cmd_line_count + 1));
		if (cmd_lines->cmd_info[line].tokens == NULL)
			return (ERR_MALLOC);
		copy_token(cmd_lines->cmd_lines[line], cmd_lines->cmd_info[line].tokens, cmd_lines->cmd_info[line].token_count);
		redir_check(&cmd_lines->cmd_info[line]);
		//malloc protect
		
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:48:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/24 15:54:04 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_exec_tokens(struct s_cmd_info *cmd_struct)
{
	int exec_token;
	int	token_n;

	token_n = 0;
	exec_token = 0;
	while (token_n < cmd_struct->token_count)
	{
		if (cmd_struct->tokens[token_n][0] != '<' && cmd_struct->tokens[token_n][0] != '>')
		{
			cmd_struct->pipe_cmd.exec_line[exec_token] = ft_strdup(cmd_struct->tokens[token_n]);
			exec_token++;
		}
		else if (cmd_struct->tokens[token_n][0] == '<' || cmd_struct->tokens[token_n][0] == '>')
		{
			if (cmd_struct->tokens[token_n + 1] == NULL)
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
				return(-1);//(ERR_INPUT);
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
	cmd_struct->pipe_cmd.exec_line = malloc(sizeof(char *) * (exec_len + 1));
	//malloc protection
	cmd_struct->pipe_cmd.exec_line[exec_len] = NULL;
	find_exec_tokens(cmd_struct);
	return (0);
}

static int	open_fd(struct s_cmd_info *cmd_struct)
{
	if (cmd_struct->has_infile == 1)
		cmd_struct->pipe_cmd.fd_in = open(cmd_struct->infile, O_RDONLY);
	else
		cmd_struct->pipe_cmd.fd_in = 0;
	if (cmd_struct->has_outfile == 1)
		cmd_struct->pipe_cmd.fd_out = open(cmd_struct->outfile, O_RDONLY | O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		cmd_struct->pipe_cmd.fd_out = 1;
	return (0);
}

static int	make_pipe_cmd(struct s_cmd_info *cmd_struct)
{
	make_exec_line(cmd_struct);
	open_fd(cmd_struct);
	return (0);
}

static int	redir_check(struct s_cmd_info *cmd_struct)
{
	int	i;

	i = 0;
	while (i < cmd_struct->token_count)
	{
		if (cmd_struct->tokens[i][0] == '<')
		{
			if (cmd_struct->has_infile == 1)
				free(cmd_struct->infile);
			cmd_struct->has_infile = 1;
			cmd_struct->infile = ft_strdup(cmd_struct->tokens[i + 1]);
		}
		
		if (cmd_struct->tokens[i][0] == '>')
		{
			if (cmd_struct->has_outfile == 1)
				free(cmd_struct->outfile);
			cmd_struct->has_outfile = 1;
			cmd_struct->outfile = ft_strdup(cmd_struct->tokens[i + 1]);
		}
		i++;
	}
	return (0);
}

static int	copy_token(char **src_str, char **dest_str, int count)//cmd_lines->cmd_lines[line], cmd_lines->cmd_info[line].tokens);
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

int	make_cmd_structs(struct s_cmd_lines *cmd_lines)
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
		cmd_lines->cmd_info[line].has_infile = 0;
		cmd_lines->cmd_info[line].has_outfile = 0;
		cmd_line_count = 0;
		while (cmd_lines->cmd_lines[line][cmd_line_count])
			cmd_line_count++;
		cmd_lines->cmd_info[line].token_count = cmd_line_count;
		cmd_lines->cmd_info[line].tokens = malloc(sizeof(char *) * (cmd_line_count + 1));
		if (cmd_lines->cmd_info[line].tokens == NULL)
			return (-1);//(ERR_MALLOC);
		copy_token(cmd_lines->cmd_lines[line], cmd_lines->cmd_info[line].tokens, cmd_lines->cmd_info[line].token_count);
		redir_check(&cmd_lines->cmd_info[line]);
		//malloc protect
		make_pipe_cmd(&cmd_lines->cmd_info[line]);
		// printf("debug\n");

		line++;
	}
	return (0);
}
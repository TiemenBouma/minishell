/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:48:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/08 10:40:36 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;


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

static int	make_exec_line(struct s_cmd_info *cmd_struct)
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


static int	copy_token(char **src_str, char **dest_str, int count)//main_struct->cmd_lines[line], main_struct->cmd_struct_arr[line].tokens);
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

void	set_err(struct s_cmd_info *cmd_struct)
{
	//cmd_struct->set_file_err = 1;
	cmd_struct->has_infile = 0;
	cmd_struct->has_outfile = 0;
	cmd_struct->has_appendfile = 0;
	cmd_struct->has_heredoc = 0;
	//close(S_IN);//cmd_struct->exec.fd_in = S_IN;
	cmd_struct->exec.fd_out = S_OUT;
	//cmd_struct->exec.exec_line[0] = NULL;
}

void	init_cmd_struct(struct s_main *main_struct, struct s_cmd_info *cmd_struct, int line)
{
	cmd_struct->cmd_index = line;
	cmd_struct->exec.cmd_count = main_struct->cmd_count;
	cmd_struct->has_infile = 0;
	cmd_struct->has_outfile = 0;
	cmd_struct->has_appendfile = 0;
	cmd_struct->exec.fd_out = 1;
	cmd_struct->exec.fd_in = 0;
	cmd_struct->has_heredoc = 0;
	cmd_struct->heredoc_fd_opened = 0;
	cmd_struct->heredoc_filename = NULL;
	cmd_struct->infile = NULL;
	cmd_struct->outfile = NULL;
	cmd_struct->env_llist = main_struct->env_llist;
	cmd_struct->pid_child = 1;
	cmd_struct->exec.heredoc = NULL;
	cmd_struct->arr_env_list = NULL;
	cmd_struct->err_syntax = 0;
	cmd_struct->set_file_err = 0;
}

int	make_cmd_structs(struct s_main *main_struct)
{
	int line;
	int	cmd_line_count;
	
	main_struct->cmd_count = 0;
	line = 0;
	cmd_line_count = 0;
	main_struct->cmd_count = 0;
	while (main_struct->cmd_lines[main_struct->cmd_count])
		main_struct->cmd_count++;
	main_struct->cmd_struct_arr = malloc(sizeof(struct s_cmd_info) * main_struct->cmd_count);
	
	while (line < main_struct->cmd_count)
	{
		cmd_line_count = 0;
		while (main_struct->cmd_lines[line][cmd_line_count])
			cmd_line_count++;
		main_struct->cmd_struct_arr[line].token_count = cmd_line_count;
		main_struct->cmd_struct_arr[line].curr_line_tokens = malloc(sizeof(char *) * (cmd_line_count + 1));
		if (main_struct->cmd_struct_arr[line].curr_line_tokens == NULL)
			exit (1);//(ERR_MALLOC);
		main_struct->cmd_struct_arr[line].curr_line_tokens[cmd_line_count] = NULL;
		copy_token(main_struct->cmd_lines[line], main_struct->cmd_struct_arr[line].curr_line_tokens, main_struct->cmd_struct_arr[line].token_count);
		init_cmd_struct(main_struct, &main_struct->cmd_struct_arr[line], line);
		g_pipe_heredoc[0][0] = line;
		heredoc_redir_check(&main_struct->cmd_struct_arr[line]);
		line++;
	}
	line = 0;
	while (line < main_struct->cmd_count)
	{
		redir_check(&main_struct->cmd_struct_arr[line]);
		make_exec_line(&main_struct->cmd_struct_arr[line]);
		add_path(main_struct->cmd_struct_arr[line].exec.exec_line, main_struct->root_paths);
		line++;
	}
	return (1);
}

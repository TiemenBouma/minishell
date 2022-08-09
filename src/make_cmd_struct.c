/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:48:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/09 11:42:23 by tbouma           ###   ########.fr       */
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
		if (cmd_struct->curr_line_tokens[token_n][0] != '<' && cmd_struct->curr_line_tokens[token_n][0] != '>')
		{
			cmd_struct->exec.exec_line[exec_token] = ft_strdup(cmd_struct->curr_line_tokens[token_n]);
			exec_token++;
		}
		else if (cmd_struct->curr_line_tokens[token_n][0] == '<' || cmd_struct->curr_line_tokens[token_n][0] == '>')
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
	int i;
	int	exec_len;

	i = 0;
	exec_len = 0;
	while (i < cmd_struct->token_count)
	{
		if (cmd_struct->curr_line_tokens[i][0] != '<' && cmd_struct->curr_line_tokens[i][0] != '>')
			exec_len++;
		else if (cmd_struct->curr_line_tokens[i][0] == '<' || cmd_struct->curr_line_tokens[i][0] == '>')
		{
			if (cmd_struct->curr_line_tokens[i + 1] == NULL)
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
	cmd_struct->exec.exec_line = malloc(sizeof(char *) * (exec_len + 1));
	//malloc protection
	cmd_struct->exec.exec_line[exec_len] = NULL;
	find_exec_tokens(cmd_struct);
	
	return (0);
}

static int	open_fd_in(struct s_cmd_info *cmd_struct)
{
	if (cmd_struct->has_infile >= 1)
		cmd_struct->exec.fd_in = open(cmd_struct->infile, O_RDONLY);
	//printf("%d\n", cmd_struct->exec.fd_in);
	if (cmd_struct->exec.fd_in < 0)
	{
		ft_putstr_fd("Bash: ", 2);
		ft_putstr_fd(cmd_struct->infile, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return(-1);
	}
	return (1);
}

static int	open_fd_out(struct s_cmd_info *cmd_struct)
{
	if (cmd_struct->has_outfile >= 1)
		cmd_struct->exec.fd_out = open(cmd_struct->outfile, O_RDONLY | O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd_struct->exec.fd_out < 0)
	{
		ft_putstr_fd("Bash: ", 2);
		ft_putstr_fd(cmd_struct->outfile, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		exit(-1);
	}
	return (1);
}

static int	redir_check(struct s_cmd_info *cmd_struct)
{
	int	i;

	i = 0;
	while (i < cmd_struct->token_count)
	{
		if (cmd_struct->curr_line_tokens[i][0] == '<')
		{
			if (cmd_struct->has_infile >= 1)
				free(cmd_struct->infile);
			cmd_struct->has_infile++;
			cmd_struct->infile = ft_strdup(cmd_struct->curr_line_tokens[i + 1]);
			if (open_fd_in(cmd_struct) == -1)
				return (-1);
		}
		
		if (cmd_struct->curr_line_tokens[i][0] == '>')
		{
			if (cmd_struct->has_outfile >= 1)
				free(cmd_struct->outfile);
			cmd_struct->has_outfile++;
			cmd_struct->outfile = ft_strdup(cmd_struct->curr_line_tokens[i + 1]);
			if(open_fd_out(cmd_struct) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}

static int	copy_token(char **src_str, char **dest_str, int count)//main_struct->cmd_lines[line], main_struct->curr_cmd_info[line].tokens);
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

int	make_cmd_structs(struct s_main *main_struct)
{
	int line;
	int	cmd_line_count;
	
	line = 0;
	cmd_line_count = 0;
	while (main_struct->cmd_lines[main_struct->cmd_count])
		main_struct->cmd_count++;
	main_struct->curr_cmd_info = malloc(sizeof(struct s_cmd_info) * main_struct->cmd_count);
	while (line < main_struct->cmd_count)
	{
		main_struct->curr_cmd_info[line].exec.cmd_count = main_struct->cmd_count;
		main_struct->curr_cmd_info[line].has_infile = 0;
		main_struct->curr_cmd_info[line].has_outfile = 0;
		main_struct->curr_cmd_info[line].exec.fd_out = 1;
		main_struct->curr_cmd_info[line].exec.fd_in = 0;
		cmd_line_count = 0;
		while (main_struct->cmd_lines[line][cmd_line_count])
			cmd_line_count++;
		main_struct->curr_cmd_info[line].token_count = cmd_line_count;
		main_struct->curr_cmd_info[line].curr_line_tokens = malloc(sizeof(char *) * (cmd_line_count + 1));
		if (main_struct->curr_cmd_info[line].curr_line_tokens == NULL)
			exit (1);//(ERR_MALLOC);
		main_struct->curr_cmd_info[line].curr_line_tokens[cmd_line_count] = NULL;
		copy_token(main_struct->cmd_lines[line], main_struct->curr_cmd_info[line].curr_line_tokens, main_struct->curr_cmd_info[line].token_count);
		if (redir_check(&main_struct->curr_cmd_info[line])  == -1)
			return (-1);
		//malloc protect
		make_exec_line(&main_struct->curr_cmd_info[line]);
		//if (main_struct->curr_cmd_info[line].token_count != 0)
		add_path(main_struct->curr_cmd_info[line].exec.exec_line, main_struct->root_paths);
		line++;
	}
	return (1);
}

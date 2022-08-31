/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:48:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/31 10:36:09 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_arrow_sign(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (SMALLER);
	if (ft_strncmp(str, ">", 2) == 0)
		return (GREATER);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (HEREDOC);
	return (0);
}

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
	int i;
	int	exec_len;
	//int	value;

	i = 0;
	exec_len = 0;
	while (i < cmd_struct->token_count)
	{
		//value = is_arrow_sign(cmd_struct->curr_line_tokens[i]);
		if (!is_arrow_sign(cmd_struct->curr_line_tokens[i]))//(value != GREATER  && value != SMALLER)//(cmd_struct->curr_line_tokens[i][0] != '<' && cmd_struct->curr_line_tokens[i][0] != '>')
		{
			exec_len++;
		}
		else if (is_arrow_sign(cmd_struct->curr_line_tokens[i]))//(value == GREATER || value == SMALLER)//(cmd_struct->curr_line_tokens[i][0] == '<' || cmd_struct->curr_line_tokens[i][0] == '>')
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
	if (cmd_struct->exec.fd_in != 0)
	{
		//printf("close(cmd_struct->exec.fd_in); %d\n", cmd_struct->exec.fd_in);
		close(cmd_struct->exec.fd_in);
		//cmd_struct->exec.fd_in = 0;
	}
	cmd_struct->exec.fd_in = open(cmd_struct->infile, O_RDONLY);
	//printf("%d\n", cmd_struct->exec.fd_in);
	if (cmd_struct->exec.fd_in < 0)
	{
		cmd_struct->set_file_err = 1;
		ft_putstr_fd("Bash: ", 2);
		ft_putstr_fd(cmd_struct->infile, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		//close(0);
		//cmd_struct->exec.fd_in = 0;
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

static int	open_fd_out_append(struct s_cmd_info *cmd_struct)
{
	if (cmd_struct->has_appendfile >= 1)
		cmd_struct->exec.fd_out = open(cmd_struct->appendfile, O_RDONLY | O_CREAT | O_RDWR | O_APPEND, 0644);
	if (cmd_struct->exec.fd_out < 0)
	{
		ft_putstr_fd("Bash: ", 2);
		ft_putstr_fd(cmd_struct->appendfile, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		exit(-1);
	}
	return (1);
}

static int	heredoc_redir_check(struct s_cmd_info *cmd_struct)
{
		int	i;
	int	total_heredoc;
	int	curr_heredoc;

	i = 0;
	curr_heredoc = 0;
	total_heredoc = heredoc_counter(cmd_struct->curr_line_tokens);
	while (i < cmd_struct->token_count)
	{
		if (is_arrow_sign(cmd_struct->curr_line_tokens[i]) == HEREDOC) // HEREDOC WILL BE MADE HERE IN A FILE
		{
			curr_heredoc++;
			// cmd_struct->has_heredoc = 2;
			// if (cmd_struct->has_infile == 2)
			// {
			// 	//printf("close(cmd_struct->exec.fd_in);%d\n", cmd_struct->exec.fd_in);
			// 	close(cmd_struct->exec.fd_in);
			// 	cmd_struct->exec.fd_in = 0;
			// 	cmd_struct->has_infile = 1;
			// }
			if (total_heredoc > curr_heredoc)
			{
				dummy_heredoc(cmd_struct->curr_line_tokens[i + 1]);
			}
			if (total_heredoc == curr_heredoc)
			{
				//cmd_struct->heredoc = ft_strdup(cmd_struct->curr_line_tokens[i + 1]);
				heredoc(cmd_struct->curr_line_tokens[i + 1], cmd_struct->heredoc_pipe);
			}
		}
		i++;
	}
	return (0);
}

static int	redir_check(struct s_cmd_info *cmd_struct)
{
	int	i;
	int	total_heredoc;
	int	curr_heredoc;

	i = 0;
	curr_heredoc = 0;
	total_heredoc = heredoc_counter(cmd_struct->curr_line_tokens);
	//printf("total heredocs: %d\n", total_heredoc);
	while (i < cmd_struct->token_count)
	{
		if (is_arrow_sign(cmd_struct->curr_line_tokens[i]) == HEREDOC) // HEREDOC WILL BE MADE HERE IN A FILE
		{
			curr_heredoc++;
			cmd_struct->has_heredoc = 2;
			if (cmd_struct->has_infile == 2)
			{
				if (cmd_struct->exec.fd_in >= 0)
				{
					//printf("close(cmd_struct->exec.fd_in);%d\n", cmd_struct->exec.fd_in);
					close(cmd_struct->exec.fd_in);
					//cmd_struct->exec.fd_in = 0;//NEW NEEDED????????????????
				}
				//cmd_struct->exec.fd_in = 0;
				cmd_struct->has_infile = 1;
			}
			//---------------------------------------
			// if (total_heredoc > curr_heredoc)
			// {
			// 	dummy_heredoc(cmd_struct->curr_line_tokens[i + 1]);
			// }
			// if (total_heredoc == curr_heredoc)
			// {
			// 	//cmd_struct->heredoc = ft_strdup(cmd_struct->curr_line_tokens[i + 1]);
			// 	heredoc(cmd_struct->curr_line_tokens[i + 1], cmd_struct->heredoc_pipe);
			// }
			//-----------------------------------------
			
			// if (open_fd_in_heredoc(cmd_struct) == -1)
			// 	return (-1);
		}
		if (is_arrow_sign(cmd_struct->curr_line_tokens[i]) == SMALLER)
		{
			if (cmd_struct->infile)
				free(cmd_struct->infile);
			if ( cmd_struct->has_heredoc == 2)
				cmd_struct->has_heredoc = 1;
			cmd_struct->has_infile = 2;
			cmd_struct->infile = ft_strdup(cmd_struct->curr_line_tokens[i + 1]);

			if (open_fd_in(cmd_struct) == -1)
				return (-1);
		}
		
		if (is_arrow_sign(cmd_struct->curr_line_tokens[i]) == GREATER)
		{
			if (cmd_struct->has_outfile >= 1)
				free(cmd_struct->outfile);
			cmd_struct->has_outfile++;
			cmd_struct->outfile = ft_strdup(cmd_struct->curr_line_tokens[i + 1]);
			if(open_fd_out(cmd_struct) == -1)
				return (-1);
		}
		if (is_arrow_sign(cmd_struct->curr_line_tokens[i]) == APPEND)
		{
			if (cmd_struct->has_appendfile >= 1)
				free(cmd_struct->appendfile);
			cmd_struct->has_appendfile++;
			cmd_struct->appendfile = ft_strdup(cmd_struct->curr_line_tokens[i + 1]);
			if(open_fd_out_append(cmd_struct) == -1)
				return (-1);
		}
		//if  is APPEND
		i++;
	}
	// printf("has heredoc= %d\n", cmd_struct->has_heredoc);
	// printf("has infile= %d\n", cmd_struct->has_infile);
	if (cmd_struct->has_heredoc == 2 && cmd_struct->exec.fd_in != 0)
	{
		//printf("close(cmd_struct->exec.fd_in);%d\n", cmd_struct->exec.fd_in);
		close(cmd_struct->exec.fd_in);
		//cmd_struct->exec.fd_in = 0;
	}
	if (cmd_struct->has_infile == 2 && cmd_struct->has_heredoc > 0)
	{
		//printf("close(cmd_struct->heredoc_pipe[0]);%d\n", cmd_struct->heredoc_pipe[0]);
		close(cmd_struct->heredoc_pipe[0]);
	}
	return (1);
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
	cmd_struct->set_file_err = 0;
}

int	make_cmd_structs(struct s_main *main_struct)
{
	int line;
	int	cmd_line_count;
	
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
		heredoc_redir_check(&main_struct->cmd_struct_arr[line]);
		line++;
	}
	line = 0;
	while (line < main_struct->cmd_count)
	{
		
		
		redir_check(&main_struct->cmd_struct_arr[line]);
		// if (redir_check(&main_struct->cmd_struct_arr[line])  == -1)
		// 	return (-1);//set_err(&main_struct->cmd_struct_arr[line]);//main_struct->cmd_struct_arr[line].set_err = 1;
		// if (main_struct->cmd_struct_arr[line].has_heredoc == 1)
		// 	main_struct->has_heredoc = 1;
		//malloc protect
		make_exec_line(&main_struct->cmd_struct_arr[line]);
		//if (main_struct->cmd_struct_arr[line].token_count != 0)

		add_path(main_struct->cmd_struct_arr[line].exec.exec_line, main_struct->root_paths);
		line++;
	}
	return (1);
}

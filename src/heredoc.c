/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:20:23 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/01 15:58:18 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"

int g_sig;

void	sigint_handler_nonl(int sig)
{
	//write(2, "DEBUG1\n", 7);
	// int save_fd = dup(STDIN_FILENO);
	// close(STDIN_FILENO);
	//ft_suppress_output();
	g_sig = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line(" ", 1);
	rl_redisplay();
	// dup2(save_fd, STDIN_FILENO);
	(void) sig;
}

// static void	sigint_here_doc_handler(int sig)
// {
// 	int	pipefd[2];

// 	g_sig = 1;
// 	(void) sig;
// 	if (pipe(pipefd) < 0)
// 		perror("Pipe: ");
// 	dup2(pipefd[0], STDIN_FILENO);
// 	write(pipefd[1], "\n\n", 2);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// }

int heredoc_counter(char **curr_line_tokens)
{
	int i;
	int	heredoc_counter;

	heredoc_counter = 0;
	i = 0;
	while(curr_line_tokens[i])
	{
		if (is_arrow_sign(curr_line_tokens[i]) == HEREDOC)
			heredoc_counter++;
		i++;
	}
	return (heredoc_counter);
}

// char	*make_heredoc_filename(int index)
// {
// 	char	*heredoc_filename;
// 	char	*num;
	
// 	num = ft_itoa(index);
// 	heredoc_filename = ft_strjoin(num, "_heredoc");
// 	free(num);
// 	return (heredoc_filename);
// }

int	heredoc(char *stop_word, int heredoc_pipe[2])
{
	//char	**gnl;
	char	**input;

	//printf("\nIN HEREDOC\n\n");

	//printf("stopWORD:%s\n", cmd_struct->heredoc);
	//err_chk(pipe((*p)[1]), 0, "");
	err_chk(pipe(heredoc_pipe), 1, "");
	input = malloc (sizeof(char **) * 2);
	if (!input)
		exit(0);
	g_sig = 0;
	signal(SIGINT, sigint_handler_nonl);
	// input = readline(">");
	while (g_sig == 0)
	{
		//signal(SIGINT, sigint_handler_nonl);
		//signal(SIGINT, sigint_here_doc_handler);
		//write(2, "> ", 2);
		if (g_sig)
			break;
		rl_on_new_line();
		get_next_line(STD_IN, input);//input = readline(">");
		if (!(input) || !ft_strncmp(*input, stop_word, ft_strlen (stop_word) + 1))
		{
			free(*input);
			free(input);
			// free(gnl[0]);
			// free(gnl);
			break ;
		}

		// 	signal(SIGINT, sigint_handler_nonl);
		write(heredoc_pipe[1], *input, ft_strlen(*input));
		free(input);
		//*input = NULL;
		write(heredoc_pipe[1], "\n", 1);
		
		// write(heredoc_pipe[1], gnl[0], ft_strlen(gnl[0]));
		// free(gnl[0]);
		// write(heredoc_pipe[1], "\n", 1);
		if (g_sig ==1)
			close(heredoc_pipe[0]);
	}
	g_sig = 0;

	signal(SIGINT, sigint_handler);
	// printf("close(heredoc_pipe[1]);%d\n", heredoc_pipe[1]);
	// printf("heredoc_pipe[0]= %d\n", heredoc_pipe[0]);
	close(heredoc_pipe[1]);
	//close(heredoc_pipe[0]);
	
	return (0);
}

int	dummy_heredoc(char *stop_word)
{
	char	**gnl;

	//printf("\nIN HEREDOC\n\n");

	//printf("stopWORD:%s\n", cmd_struct->heredoc);
	//err_chk(pipe((*p)[1]), 0, "");
	gnl = malloc (sizeof(char **) * 2);
	if (!gnl)
		exit(0);
	while (1)
	{
		if (get_next_line(0, gnl) == -1 || ft_strncmp(gnl[0], stop_word,
				ft_strlen (stop_word) + 1) == 0)
		{
			free(gnl[0]);
			free(gnl);
			break ;
		}
		if (!gnl)
			signal(SIGINT, sigint_handler_nonl);
		free(gnl[0]);
	}
	return (0);
}

// int	heredoc(struct s_cmd_info *cmd_struct, char *stop_word, char *heredoc_filename)
// {
// 	//int		fd;
// 	char	**gnl;
	
// 	//fd = open(heredoc_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd < 0)
// 		exit (0);
// 	// err_chk(dup2(fd, S_OUT), 1, "");
// 	gnl = malloc (sizeof(char **) * 2);
// 	if (!gnl)
// 		exit(0);
// 	while (1)
// 	{
// 		if (get_next_line(0, gnl) == 0 || ft_strncmp (gnl[0], stop_word, ft_strlen (stop_word) + 1) == 0)
// 		{
// 			free(gnl[0]);
// 			free(gnl);
// 			break ;
// 		}
// 		printf("wccxz");//????
// 		write(fd, gnl[0], ft_strlen(gnl[0]));
// 		free(gnl[0]);
// 		write(fd, "\n", 1);
// 	}
// 	close(fd);
// 	return (1);
// 	return (0);
// }
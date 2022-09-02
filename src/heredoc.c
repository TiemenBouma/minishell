/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:20:23 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/02 10:54:21 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"

int g_sig;

void	sigint_handler_heredoc(int sig)
{

	int	temp_pipe[2];

	(void) sig;
	if (pipe(temp_pipe) < 0)
		perror("Pipe: ");
	dup2(temp_pipe[0], STDIN_FILENO);
	write(temp_pipe[1], "\n\n", 2);
	close(temp_pipe[0]);
	close(temp_pipe[1]);

	g_sig = 1;

	(void) sig;
}


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


int	heredoc(char *stop_word, int heredoc_pipe[2])
{
	char	*input;

	// input = malloc (sizeof(char **) * 2);
	// if (!input)
	// 	exit(0);
	g_sig = 0;

	signal(SIGINT, sigint_handler_heredoc);
	// input = readline(">");
	while (g_sig == 0)
	{
		//signal(SIGINT, sigint_handler_nonl);
		//signal(SIGINT, sigint_here_doc_handler);
		//write(2, "> ", 2);
		if (g_sig)
			break;
		rl_on_new_line();
		
		input = readline(">");//get_next_line(STD_IN, input);
		if (!(input) || !ft_strncmp(input, stop_word, ft_strlen (stop_word) + 1))
		{
			//free(*input);
			free(input);
			// free(gnl[0]);
			// free(gnl);
			break ;
		}

		// 	signal(SIGINT, sigint_handler_nonl);
		write(heredoc_pipe[P_IN], input, ft_strlen(input));
		free(input);
		//*input = NULL;
		write(heredoc_pipe[P_IN], "\n", 1);
		
		// write(heredoc_pipe[1], gnl[0], ft_strlen(gnl[0]));
		// free(gnl[0]);
		// write(heredoc_pipe[1], "\n", 1);
		if (g_sig ==1)
			close(heredoc_pipe[P_OUT]);
	}
	g_sig = 0;

	signal(SIGINT, sigint_handler);
	// printf("close(heredoc_pipe[1]);%d\n", heredoc_pipe[1]);
	close(heredoc_pipe[P_IN]); 
	//close(heredoc_pipe[0]);
	
	return (0);
}

int	dummy_heredoc(char *stop_word)
{
	char	**gnl;

	g_sig = 0;

	signal(SIGINT, sigint_handler_heredoc);
	gnl = malloc (sizeof(char **) * 2);
	if (!gnl)
		exit(0);
	while (1)
	{
		write(2, "> ", 2);
		if (get_next_line(0, gnl) == -1 || ft_strncmp(gnl[0], stop_word,
				ft_strlen (stop_word) + 1) == 0)
		{
			free(gnl[0]);
			free(gnl);
			break ;
		}
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
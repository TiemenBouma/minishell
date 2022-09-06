/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:20:23 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/05 12:33:06 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"

extern int **g_pipe_heredoc;

// int g_sig;
//int g_pipe_heredoc[2];

void	sigint_handler_heredoc(int sig)
{
	//g_sig = 1;
	(void) sig;
	close(g_pipe_heredoc[g_pipe_heredoc[0][0]][P_IN]);
	exit(10);
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


int	heredoc(char *stop_word, int index)//, int heredoc_pipe[2])
{
	char	*input;

	//g_sig = 0;
	//close(g_pipe_heredoc[P_OUT]);
	signal(SIGINT, sigint_handler_heredoc);// we need to close pipe in if signal;
	while (1)//(g_sig == 0)
	{
		// if (g_sig)
		// 	break;
		input = readline("> ");
		if (!(input) || !ft_strncmp(input, stop_word, ft_strlen (stop_word) + 1))
		{
			free(input);
			break ;
		}
		write(g_pipe_heredoc[index + 1][P_IN], input, ft_strlen(input));
		free(input);
		write(g_pipe_heredoc[index + 1][P_IN], "\n", 1);
		// if (g_sig ==1)
		// {
		// 	close(heredoc_pipe[P_OUT]);
		// }
	}
	//g_sig = 0;

	signal(SIGINT, sigint_handler);
	close(g_pipe_heredoc[index + 1][P_IN]); 
	return (0);
}

int	dummy_heredoc(char *stop_word)
{
	char	**gnl;

	//g_sig = 0;

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
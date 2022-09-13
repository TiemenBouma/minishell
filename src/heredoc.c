/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:20:23 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/07 10:16:21 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"

extern int	**g_pipe_heredoc;

void	sigint_handler_heredoc(int sig)
{

	ft_suppress_output();
	(void) sig;
	close(g_pipe_heredoc[g_pipe_heredoc[0][0]][P_IN]);
	exit(10);
}

int	heredoc_counter(char **curr_line_tokens)
{
	int i;
	int	heredoc_counter;

	heredoc_counter = 0;
	i = 0;
	while (curr_line_tokens[i])
	{
		if (is_arrow_sign(curr_line_tokens[i]) == HEREDOC)
			heredoc_counter++;
		i++;
	}
	return (heredoc_counter);
}

int	heredoc(char *stop_word, int index)
{
	char	*input;

	signal(SIGINT, sigint_handler_heredoc);
	while (1)
	{
		input = readline("> ");
		if (!(input) || !ft_strncmp(input,
				stop_word, ft_strlen (stop_word) + 1))
		{
			free(input);
			break ;
		}
		write(g_pipe_heredoc[index + 1][P_IN], input, ft_strlen(input));
		free(input);
		write(g_pipe_heredoc[index + 1][P_IN], "\n", 1);
	}


	signal(SIGINT, sigint_handler);
	close(g_pipe_heredoc[index + 1][P_IN]);
	return (0);
}

int	dummy_heredoc(char *stop_word)
{
	char	*input;


	signal(SIGINT, sigint_handler_heredoc);
	while (1)
	{

		input = readline("> ");
		if (!(input) || !ft_strncmp(input,
				stop_word, ft_strlen (stop_word) + 1))
		{
			free(input);
			break ;
		}
	}
	signal(SIGINT, sigint_handler);
	return (0);
}

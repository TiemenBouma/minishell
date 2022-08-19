/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:20:23 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/19 10:45:47 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"

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

char	*make_heredoc_filename(int index)
{
	char	*heredoc_filename;
	char	*num;
	
	num = ft_itoa(index);
	heredoc_filename = ft_strjoin(num, "_heredoc");
	free(num);
	return (heredoc_filename);
}

int	heredoc(char *stop_word, int heredoc_pipe[2])
{
	char	**gnl;

	//printf("\nIN HEREDOC\n\n");

	//printf("stopWORD:%s\n", cmd_struct->heredoc);
	//err_chk(pipe((*p)[1]), 0, "");
	err_chk(pipe(heredoc_pipe), 1, "");
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
		write(heredoc_pipe[1], gnl[0], ft_strlen(gnl[0]));
		free(gnl[0]);
		write(heredoc_pipe[1], "\n", 1);
	}
	printf("close(heredoc_pipe[1]);%d\n", heredoc_pipe[1]);
	close(heredoc_pipe[1]);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 09:55:34 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/15 15:37:22 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes_on_pipes(char *line)
{
	//if "" are around a | character it should not split.
	
	return (0); 
}

int	pipe_split(char *line)
{
	check_quotes_on_pipes(line);
	return (0);
}

char	***parse_line(char *line)
{
	int		pipe_count;
	int		i;
	char	**split_pipe;
	char	***cmd_arr;

	pipe_count = 0;
	i = 0;
	split_pipe = ft_split(line, '|');
	while (split_pipe[pipe_count] != NULL)
		pipe_count++;
	cmd_arr = malloc(sizeof(char **) * pipe_count + 1);
	while (i < pipe_count)
	{
		cmd_arr[i] = ft_split(split_pipe[i], ' ');
		i++;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

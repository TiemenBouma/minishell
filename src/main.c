/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 15:52:01 by tiemen        #+#    #+#                 */
/*   Updated: 2022/07/14 14:17:28 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_line(char *line)
{
	int		pipe_count;
	int i;
	char	**split_pipe;
	char	***cmd_arr;
	
	pipe_count = 0;
	i = 0;
	split_pipe = ft_split(line, '|');
	while (split_pipe[i] != NULL)
		pipe_count++;
	cmd_arr = malloc(sizeof(char **) * pipe_count);
	while (i < pipe_count)
	{
		cmd_arr[i] = ft_split(split_pipe[i], ' ');
		i++;
	}
	
}

// int	make_history(char *str)
// {
	
// }

int	main(int argc, char **argv, char **envp)
{
	HIST_ENTRY **the_history_list;
	char	*str;
	char	**root_path;
	//char	*cmd_path;
	
	(void) argc;
	(void) argv;
	root_path = find_path(envp);
	str = readline("SuperShell: ");
	printf("%s\n", root_path[0]);
	printf("readline:%s\n", str);
	free_stuff(str);

	
}

// gcc main.c -lreadline

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 15:52:01 by tiemen        #+#    #+#                 */
/*   Updated: 2022/07/14 20:06:11 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	***parse_line(char *line)
{
	int		pipe_count;
	int i;
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

// int	make_history(char *str)
// {
	
// }

int	main(int argc, char **argv, char **envp)
{
	// HIST_ENTRY **the_history_list;
	char	*str;
	char	**root_path;
	//char	*cmd_path;
	int		i, j;
	char	***cmd_arr;
	
	i = 0;
	(void) argc;
	(void) argv;
	root_path = find_path(envp);
	str = readline("SuperShell: ");
	while (root_path[i])
	{
		printf("%s\n", root_path[i]);
		i++;
	}
	i = 0;
	printf("readline:%s\n", str);
	cmd_arr = parse_line(str);
	while (cmd_arr[i])
	{
		j = 0;
		while (cmd_arr[i][j])
		{
			printf("%s\n", cmd_arr[i][j]);
			j++;
		}
		i++;
	}
	free_stuff(str);

	
}

// gcc main.c -lreadline

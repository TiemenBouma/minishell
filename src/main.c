/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 15:52:01 by tiemen        #+#    #+#                 */
/*   Updated: 2022/07/14 10:31:30 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_history(char *str)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	HIST_ENTRY ** the_history_list;
	char	*str;
	char	**root_path;
	char	*cmd_path;
	
	(void) argc;
	(void) argv;
	root_path = find_path(envp);
	str = readline("SuperShell: ");
	
	printf("readline:%s\n", str);
	free_stuff(str);
	
}

// gcc main.c -lreadline

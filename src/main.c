/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/15 16:37:03 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



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
	add_history(str);
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

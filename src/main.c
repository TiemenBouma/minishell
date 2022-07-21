/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/21 12:46:10 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



// int	make_history(char *str)
// {
	
// }



int	main(void)//(int argc, char **argv, char **envp)
{
	// HIST_ENTRY **the_history_list;
	//struct s_data	d;
	char	*str;
	// char	**root_path;
	//char	*cmd_path;
	int		i, j;
	//char	***cmd_arr;
	char	**tokens;
	char	***cmds;
	int		c1, c2;
	c1 = 0;
	i = 0;
	j = 0;
	// (void) argc;
	// (void) argv;
	// root_path = find_path(envp);
	str = readline("SuperShell: ");
	//add_history(str);
	// while (root_path[i])
	// {
	// 	printf("%s\n", root_path[i]);
	// 	i++;
	// }
	i = 0;
	printf("readline:%s\n", str);
	tokens = ft_split_tokens(str, ' ');

	cmds = make_cmd_and_redir(tokens);
	while (cmds[c1])
	{
		c2 = 0;
		while (cmds[c1][c2])
		{
			printf("|%s| ", cmds[c1][c2]);
			c2++;
		}
		printf("\n");
		c1++;
	}
	free_stuff(str);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/22 11:45:40 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	struct s_cmd_lines	cmd_lines;

	(void) argc;
	(void) argv;
	cmd_lines.root_paths = find_path(envp);
	cmd_lines.input_str = readline("SuperShell: ");
	cmd_lines.all_tokens = ft_split_tokens(cmd_lines.input_str, ' ');
	cmd_lines.cmd_lines = make_cmd_lines(cmd_lines.all_tokens);
	make_cmd_structs(&cmd_lines);
	
	return (0);
}
	// int		c1, c2;
	// c1 = 0;
	// while (cmd_lines.cmd_lines[c1])
	// {
	// 	c2 = 0;
	// 	while (cmd_lines.cmd_lines[c1][c2])
	// 	{
	// 		printf("|%s| ", cmd_lines.cmd_lines[c1][c2]);
	// 		c2++;
	// 	}
	// 	printf("\n");
	// 	c1++;
	// }


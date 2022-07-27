/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/27 15:27:45 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)//(int argc, char **argv, char **envp)
{
	struct s_cmd_lines	var;
	t_node	*env_list;

	extern char **environ;
	// (void) argc;
	// (void) argv;
	var.root_paths = find_path(environ);
	env_list = add_env_to_list(environ);
	print_list(env_list);
	while (1)
	{
		var.input_str = readline("SuperShell: ");
		var.all_tokens = ft_split_tokens(var.input_str);
		var.cmd_lines = make_cmd_lines(var.all_tokens);
		make_cmd_structs(&var);
		//print_structs(&var);
		exec(&var);
		free_struct(&var);
	}
	return (0);
}

	// int		c1;
	// c1 = 0;
	// while (var.cmd_info->tokens[c1])
	// {
	// 	printf("|%s| ", var.cmd_info[0].tokens[c1]);
	// 	c1++;
	// }
	// printf("\n");

	// int		c1, c2;
	// c1 = 0;
	// while (var.var[c1])
	// {
	// 	c2 = 0;
	// 	while (var.var[c1][c2])
	// 	{
	// 		printf("|%s| ", var.var[c1][c2]);
	// 		c2++;
	// 	}
	// 	printf("\n");
	// 	c1++;
	// }
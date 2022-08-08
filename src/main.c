/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/08/08 13:51:51 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	struct s_cmd_lines	var;
	extern char **environ;

	var.root_paths = find_path(environ);
	var.env_list = add_env_to_list(environ);
	signal(SIGINT, sigint_handler);
	print_linked_list(&var.env_list);
	ft_remove_node(&var.env_list, "MAKELEVEL");
	print_linked_list(&var.env_list);
	
	while (1)
	{
		print_linked_list(&var.env_list);
		var.input_str = readline("SuperShell: ");
		//signals();
		expand_var(&var.input_str, &var.env_list);
		var.all_tokens = ft_split_tokens(var.input_str);
		if (var.all_tokens[0] == NULL)
			continue ;
		var.cmd_lines = make_cmd_lines(var.all_tokens);
		make_cmd_structs(&var);
		print_structs(&var);
		exec(&var);
		free_struct(&var);
	}
	return (0);
}

	//print_linked_list(&var.env_list);
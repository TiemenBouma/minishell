/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/29 16:52:31 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	struct s_cmd_lines	var;
	t_node	*env_list;
	extern char **environ;

	var.root_paths = find_path(environ);
	env_list = add_env_to_list(environ);

	//print_linked_list(env_list);
	while (1)
	{
		var.input_str = readline("SuperShell: ");
		expand_var(&var.input_str, &env_list);
		var.all_tokens = ft_split_tokens(var.input_str);
		var.cmd_lines = make_cmd_lines(var.all_tokens);

		make_cmd_structs(&var);
		//ft_remove_node(&env_list, "USER");
		//print_structs(&var);
		exec(&var);
		free_struct(&var);
	}
	return (0);
}


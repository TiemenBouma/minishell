/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/08/09 09:45:09 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	struct s_main	main_struct;
	extern char **environ;

	main_struct.root_paths = find_path(environ);
	main_struct.env_llist = add_env_to_list(environ);
	//signal(SIGINT, sigint_handler);
	signals_handeler();
	
	while (1)
	{
		main_struct.input_str = readline("SuperShell: ");
		//signal(SIGINT, sigint_handler);
		if (main_struct.input_str == NULL)
			break;
		expand_variables(&main_struct.input_str, &main_struct.env_llist);
		main_struct.all_tokens = ft_split_tokens(main_struct.input_str);
		if (main_struct.all_tokens[0] == NULL)
			continue ;
		main_struct.cmd_lines = make_cmd_lines(main_struct.all_tokens);
		make_cmd_structs(&main_struct);
		//print_structs(&main_struct);
		exec(&main_struct);
		free_struct(&main_struct);
	}
	return (0);
}

	//print_linked_list(&main_struct.env_llist);
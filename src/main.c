/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/08/19 15:24:16 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	struct s_main	main_struct;
	extern char **environ;
	//char		**test_arr;
	//char	*cwd;

	main_struct.old_exit_status = 0;
	//main_struct.has_heredoc = 0;
	main_struct.env_llist = add_env_to_list(environ);
	//signals_handeler();

	
	while (1)
	{
		main_struct.root_paths = find_path(&main_struct.env_llist);
		main_struct.input_str = readline("SuperShell: ");
		add_history(main_struct.input_str);
		if (main_struct.input_str == NULL)
			break;
		expand_variables(&main_struct.input_str, &main_struct.env_llist, main_struct.old_exit_status);
		main_struct.all_tokens = ft_split_tokens(main_struct.input_str);
		if (main_struct.all_tokens[0] == NULL)
			continue ;
		main_struct.cmd_lines = make_cmd_lines(main_struct.all_tokens);
		if (make_cmd_structs(&main_struct) == -1)
		{
			free_struct(&main_struct);
			continue;
		}
		// test_arr = make_arr_from_list(&main_struct.env_llist);
		// print_dubble_str(test_arr, "testarr = ");
		print_structs(&main_struct);
		main_struct.old_exit_status = exec(&main_struct);
		free_struct(&main_struct);
		// cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
		// cwd[PATH_MAX] = '\0';
		// getcwd(cwd, MAXPATHLEN);//checked if switch worked
		// printf("cwd parent = %s\n", cwd);
		//print_structs(&main_struct);
	}
	return (main_struct.old_exit_status);
}

	//print_linked_list(&main_struct.env_llist);
		// print_dubble_str(main_struct.root_paths, "PATHS\n");
		// ft_find_and_remove_node(&main_struct.env_llist, "PATH");
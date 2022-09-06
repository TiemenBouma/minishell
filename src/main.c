/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/09/05 15:45:06 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int **g_pipe_heredoc;


int init_main_struct(struct	s_main *main_struct)
{
	extern char		**environ;

	main_struct->old_exit_status = 0;
	main_struct->env_llist = add_env_to_list(environ);
	main_struct->all_tokens = NULL;
	main_struct->cmd_count = 0;
	main_struct->cmd_lines = NULL;
	main_struct->cmd_struct_arr = NULL;
	main_struct->input_str = NULL;
	main_struct->root_paths = NULL;
	return (0);
}

//rl_catch_signals = 0;
int	main(int argc, char **argv)
{
	struct s_main	main_struct;

	g_pipe_heredoc = NULL;
	init_main_struct(&main_struct);
	signals_handeler();
	while (1)
	{
		main_struct.root_paths = find_path(&main_struct.env_llist);
		if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
			main_struct.input_str = argv[2];
		else
			main_struct.input_str = readline("SuperShell: ");
		add_history(main_struct.input_str);
		if (main_struct.input_str == NULL)
		{
			write(2, "exit\n", 5);
			free_struct(&main_struct);
			break ;
		}
		expand_variables(&main_struct.input_str, &main_struct.env_llist, main_struct.old_exit_status);
		//printf("|%s|\n", main_struct.input_str);
		main_struct.all_tokens = ft_split_tokens(main_struct.input_str);
		//print_dubble_str(main_struct.all_tokens, "Tokens");
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
		//print_structs(&main_struct);
		//printf("--------------------EXEC---------------------\n");
		main_struct.old_exit_status = exec(&main_struct);
		if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
			exit(main_struct.old_exit_status);
		//printf("-------------------endEXEC--------------------\n");
		free_struct(&main_struct);
		// cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
		// cwd[PATH_MAX] = '\0';
		// getcwd(cwd, MAXPATHLEN);//checked if switch worked
		// printf("cwd parent = %s\n", cwd);
		//print_structs(&main_struct);
	}
	free_linked_list(&main_struct.env_llist);
	return (main_struct.old_exit_status);
}

	//print_linked_list(&main_struct.env_llist);
		// print_dubble_str(main_struct.root_paths, "PATHS\n");
		// ft_find_and_remove_node(&main_struct.env_llist, "PATH");
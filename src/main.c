/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 15:52:01 by tiemen        #+#    #+#                 */
/*   Updated: 2022/09/09 16:08:22 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	**g_pipe_heredoc;

int	basic_error_handeling(struct s_main *m_s)
{
	if (m_s->all_tokens[0] == NULL)
		return (1);
	if (ft_strncmp(m_s->all_tokens[0], "|", 2) == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		m_s->old_exit_status = 2;
		return (1);
	}
	return (0);
}

int	init_m_s(struct	s_main *m_s)
{
	m_s->old_exit_status = 0;
	m_s->all_tokens = NULL;
	m_s->cmd_count = 0;
	m_s->cmd_lines = NULL;
	m_s->c_s_arr = NULL;
	m_s->input_str = NULL;
	m_s->root_paths = NULL;
	return (0);
}

//rl_catch_signals = 0;

int	main(int argc, char **argv)
{
	extern char		**environ;
	struct s_main	m_s;

	g_pipe_heredoc = NULL;
	signals_handeler();
	m_s.env_llist = add_env_to_list(environ);
	while (1)
	{
		init_m_s(&m_s);
		m_s.root_paths = find_path(&m_s.env_llist);
		if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		{
			if (ft_strncmp(argv[2], "|", 1) == 0 || argv[2][0] == ' ')
				exit (ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2));
			m_s.input_str = ft_strdup(argv[2]);
		}
		else
			m_s.input_str = readline("SuperShell: ");
		add_history(m_s.input_str);
		if (m_s.input_str == NULL)
		{
			write(2, "exit\n", 5);
			free_struct(&m_s);
			break ;
		}
		expand_variables(&m_s.input_str, &m_s.env_llist, m_s.old_exit_status);
		m_s.all_tokens = ft_split_tokens(m_s.input_str);
		
		if (basic_error_handeling(&m_s))
		{
			free_struct(&m_s);
			continue ;
		}
		m_s.cmd_lines = make_cmd_lines(m_s.all_tokens);
		if (make_cmd_structs(&m_s) == -1)
		{
			free_struct(&m_s);
			continue ;
		}
		//print_structs(&m_s);
		m_s.old_exit_status = exec(&m_s);
		if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
			exit(m_s.old_exit_status);
		free_struct(&m_s);
	}
	free_linked_list(&m_s.env_llist);
	return (m_s.old_exit_status);
}

	//print_linked_list(&m_s.env_llist);
		// print_dubble_str(m_s.root_paths, "PATHS\n");
		// ft_find_and_remove_node(&m_s.env_llist, "PATH");
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/19 09:38:02 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	exec(struct	s_main *main_struct)
{
	int i = 0;
	int rr;
	int id = 0;
	int p[2][2];
	sig_t	old_signal[2];


	



	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1

	
	while (i < main_struct->cmd_count)
	{
		rr = 0;
		i++;
		err_chk(pipe(p[CUR]), 1, "");
		old_signal[0] = signal(SIGINT, sigint_handler_in_process);
		old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
		if (main_struct->cmd_struct_arr[i - 1].exec.exec_line[0] && ft_strncmp(main_struct->cmd_struct_arr[i -1].exec.exec_line[0], "exit", 4 + 1) == 0 && main_struct->cmd_count == 1)
			ft_exit(main_struct->cmd_struct_arr[i - 1].exec.exec_line); // NEEDS A token 
		id = fork();
		err_chk(id, 1, "");
		if (id == 0)
		{
			if (main_struct->cmd_struct_arr[i - 1].has_infile == 2)
			{
				printf("TEST1\n");
				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
				
			}
			else if (main_struct->cmd_struct_arr[i - 1].has_heredoc == 2)
			{
				printf("TEST2\n");
				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT], S_IN), 1, "");
			}
			else
			{
				printf("TEST3\n");
				
				err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
			}
				
			if (main_struct->cmd_struct_arr[i - 1].exec.fd_out == 1 && main_struct->cmd_count != i)
			{
				printf("TEST4\n");
				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
			}
			else
			{
					printf("TEST5\n");

				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
			}
			if (is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]))
			{
					printf("TEST6\n");
				exec_builtin(&main_struct->cmd_struct_arr[i - 1], is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
				exit(0);
			}
				printf("TEST7\n");
			execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL);
		}
		if (main_struct->cmd_struct_arr[i - 1].has_heredoc > 0)
			close (main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT]);
		if (i > 1)
			close (p[PREV][P_OUT]);
		close (p[CUR][P_IN]);
	}
	close (p[CUR][P_OUT]);
	waitpid(id, &i, 0);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	return (WEXITSTATUS(i));
}

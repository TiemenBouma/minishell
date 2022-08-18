/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:53:02 by dkocob        #+#    #+#                 */
/*   Updated: 2022/08/18 15:41:00 by dkocob        ########   odam.nl         */
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
				printf ("Heredoc: %d \n", main_struct->cmd_struct_arr[i - 1].has_heredoc);
				if (main_struct->cmd_struct_arr[i - 1].exec.fd_in != 0 || main_struct->cmd_struct_arr[i - 1].has_heredoc != 0)
				{
					if (main_struct->cmd_struct_arr[i - 1].has_heredoc != 0)
					{
						write (2, "HEREDOC!\n", 9);
						err_chk(dup2(main_struct->cmd_struct_arr[i - 1].heredoc[P_OUT], S_IN), 1, "");
					}
					else
						err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
				}
				else
					err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
					
				if (main_struct->cmd_struct_arr[i - 1].exec.fd_out == 1 && main_struct->cmd_count != i)
					err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
				else
					err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
				if (is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]))
				{
					exec_builtin(&main_struct->cmd_struct_arr[i - 1], is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
					exit(0);
				}
				execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL);
			}
			close (p[PREV][P_OUT]);
			close (p[CUR][P_IN]);
		}
	close (p[CUR][P_OUT]);
	waitpid(id, &i, 0);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	return (WEXITSTATUS(i));
}

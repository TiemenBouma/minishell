/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/10 10:14:31 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec(struct	s_main *main_struct)
{
	int i = 0;
	int status;
	int id = 0;
	int p[2][2];
	sig_t	old_signal[2];


	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1

	
	while (i < main_struct->cmd_count)
	{
		i++;
		err_chk(pipe(p[CUR]), 1, "");
		old_signal[0] = signal(SIGINT, sigint_handler_in_process);
		old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
		if (ft_strncmp(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], "exit", 4 + 1) == 0 && main_struct->cmd_count == 1)//test exit here-------------------
		{
			printf("DEBUG\n");
			// close (p[PREV][P_OUT]);
			// close (p[CUR][P_IN]);
			// kill(getppid(), SIGUSR1);
			// waitpid(id, &i, 0);
			// signal(SIGINT, old_signal[0]);
			// signal(SIGQUIT, old_signal[1]);
			exit(2);
		} // ----------------------------------------------end test
		id = fork();
		//err_chk(id, 1, "");
		if (id == 0)
		{
			if (i == 1) //1st
			{
				printf("TEST1\n");
				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
			}
			if (i != 1) // every Other
			{
				printf("TEST2\n");
				err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
			}
			if (i != main_struct->cmd_count) //every mid
			{
				printf("TEST3\n");
				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
			}
			if (i == main_struct->cmd_count) //end
				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
			if (is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]))
			{
				exec_builtin(main_struct, main_struct->cmd_struct_arr[i - 1].exec.exec_line, is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
				exit(0);
			}
			printf("TEST4\n");
			execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL); //why if command not found exit(0)?
		}
		close (p[PREV][P_OUT]);
		close (p[CUR][P_IN]);
	}
	close (p[CUR][P_OUT]);
	waitpid(id, &status, 0);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	return (WEXITSTATUS(status));
}

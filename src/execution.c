/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/22 09:47:38 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	exec(struct	s_main *main_struct)
{
	extern char **environ;
	int i = 0;
	int rr;
	int id = 1;
	int p[2][2];
	//char	**env_return;
	sig_t	old_signal[2];
	struct s_cmd_info	curr_cmd;

	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1


	while (i < main_struct->cmd_count)
	{
		rr = 0;
		i++;
		curr_cmd = main_struct->cmd_struct_arr[i - 1];
		err_chk(pipe(p[CUR]), 1, "");
		if (curr_cmd.exec.exec_line[0] && is_builtin(curr_cmd.exec.exec_line[0]) == EXIT_BUILD && main_struct->cmd_count == 1)
			ft_exit(curr_cmd.exec.exec_line); // NEEDS A token 
		if (check_buildin_fork(&curr_cmd) == 0)
			exec_builtin(&curr_cmd, is_builtin(curr_cmd.exec.exec_line[0]));
		else
		{
			old_signal[0] = signal(SIGINT, sigint_handler_in_process);
			old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
			id = fork();
		}
		err_chk(id, 1, "");
		if (id == 0 && check_buildin_fork(&curr_cmd) == 1)//Why is is_builtin in this if statment
		{
			if (curr_cmd.has_infile == 2)
				err_chk(dup2(curr_cmd.exec.fd_in, S_IN), 1, "");
			else if (curr_cmd.has_heredoc == 2)
				err_chk(dup2(curr_cmd.heredoc_pipe[P_OUT], S_IN), 1, "");
			else
				err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");	
			if (curr_cmd.exec.fd_out == 1 && main_struct->cmd_count != i)
				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
			else
				err_chk(dup2(curr_cmd.exec.fd_out, S_OUT), 1, "");
			if (is_builtin(curr_cmd.exec.exec_line[0]) < 7)
			{
				exec_builtin(&curr_cmd, is_builtin(curr_cmd.exec.exec_line[0]));
				exit(0);
			}
			//env_return = make_arr_from_list(&main_struct->env_llist);
			if (execve(curr_cmd.exec.exec_line[0], curr_cmd.exec.exec_line, environ) == -1)// check malloc of make_arr_func is freed
			{
				perror(curr_cmd.exec.exec_line[0]);
				exit(127);	
			}
		}
		// if (is_builtin(curr_cmd.exec.exec_line[0]) < 3)
		// {
		// 	exec_builtin(&curr_cmd, is_builtin(curr_cmd.exec.exec_line[0]));
		// }
		// if (main_struct->cmd_struct_arr[i - 1].has_heredoc == 2)
		// {
		// 	printf("close (main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT]);%d\n", main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT]);
		// 	close (main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT]);
		// }
		//if (i > 1)
		//{
			printf("close (p[PREV][P_OUT]);%d\n", p[PREV][P_OUT]);
			close (p[PREV][P_OUT]);
		//}
		printf("close (p[CUR][P_IN]);%d\n", p[CUR][P_IN]);
		close (p[CUR][P_IN]);
		if (curr_cmd.has_heredoc == 2)//This might need to be on a different palce.
		{
			printf("close (main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT]);%d\n", curr_cmd.heredoc_pipe[P_OUT]);
			close (curr_cmd.heredoc_pipe[P_OUT]);
		}
	}
	printf("close (p[CUR][P_OUT]);%d\n", p[CUR][P_OUT]);
	close (p[CUR][P_OUT]);
	waitpid(id, &i, 0);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	return (WEXITSTATUS(i));
}

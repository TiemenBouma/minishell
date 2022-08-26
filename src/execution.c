/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/26 10:05:16 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	exec(struct	s_main *main_struct)
{
	extern char **environ;
	int i = 0;
	int	build_return;
	int id = 1;
	int p[2][2];
	sig_t	old_signal[2];
	struct s_cmd_info	*curr_cmd;

	build_return = -1;
	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1
	// if (main_struct->cmd_count == 1 && is_builtin(main_struct->cmd_struct_arr[i].exec.exec_line[0]) == EXIT_BUILD)
	// 	ft_exit(main_struct->cmd_struct_arr[i].exec.exec_line);

	while (i < main_struct->cmd_count)
	{
		i++;
		curr_cmd = &main_struct->cmd_struct_arr[i - 1];
		err_chk(pipe(p[CUR]), 1, "");
		if (curr_cmd->exec.exec_line[0] && is_builtin(curr_cmd->exec.exec_line[0]) == EXIT_BUILD && main_struct->cmd_count == 1)
		{
			// printf("DEBUG0\n");
			ft_exit(curr_cmd->exec.exec_line); // NEEDS A token 
			continue;
		}
		if (check_buildin_fork(curr_cmd) == 0 && curr_cmd->set_file_err == 0)
		{
			printf("DEBUG1\n");
			build_return =  exec_builtin(curr_cmd, is_builtin(curr_cmd->exec.exec_line[0]));
		}
		else if (check_buildin_fork(curr_cmd) == 0)
			printf("DEBUG2\n");
		else
		{
			printf("DEBUG3\n");
			id = fork();
		}
		old_signal[0] = signal(SIGINT, sigint_handler_in_process);
		old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
		// printf("ID= %d\n", id);
		err_chk(id, 1, "");
		if (id == 0 && check_buildin_fork(curr_cmd) == 1)//Why is is_builtin in this if statment
		{
			// printf("EXEC1\n");
			if (curr_cmd->has_heredoc == 2)
			{
				// printf("EXEC3\n");
				
				err_chk(dup2(curr_cmd->heredoc_pipe[P_OUT], S_IN), 2, "");
			}
			else if (curr_cmd->has_infile == 2 || i == 1)
			{
				// printf("EXEC2\n");
				
				err_chk(dup2(curr_cmd->exec.fd_in, S_IN), 2, "");
				// printf("EXEC2.1\n");
			}
			else
			{
				// printf("EXEC4\n");
				
				err_chk(dup2(p[PREV][P_OUT], S_IN), 2, "");	
			}
			if (curr_cmd->exec.fd_out == 1 && main_struct->cmd_count != i)
			{
				// printf("EXEC5\n");
				
				err_chk(dup2(p[CUR][P_IN], S_OUT), 2, "");
			}
			else
			{
				// printf("EXEC6\n");
				
				err_chk(dup2(curr_cmd->exec.fd_out, S_OUT), 2, "");
			}
			if (is_builtin(curr_cmd->exec.exec_line[0]) < 7 && curr_cmd->set_file_err == 0)
			{
				// printf("EXEC7\n");
				exec_builtin(curr_cmd, is_builtin(curr_cmd->exec.exec_line[0]));
				exit(0);
			}
			// printf("EXEC8\n");
			if (curr_cmd->set_file_err == 0)
			{
				// printf("EXEC9\n");
				if (execve(curr_cmd->exec.exec_line[0], curr_cmd->exec.exec_line, make_arr_from_list(&main_struct->env_llist)) == -1)// check malloc of make_arr_func is freed
				{
					// printf("EXEC9.1\n");
					if(curr_cmd->exec.exec_line[0] == NULL)
						exit(0);	
					// printf("EXEC9.2\n");
					perror(curr_cmd->exec.exec_line[0]);
					exit(127);	
				}	
				// printf("EXEC9.3\n");
			}
			else
				exit(1);
		}
		if (i > 1)
		{
			// printf("EXEC10\n");

			//printf("close (p[PREV][P_OUT]);%d\n", p[PREV][P_OUT]);
			close (p[PREV][P_OUT]);
		}
		//printf("close (p[CUR][P_IN]);%d\n", p[CUR][P_IN]);
		// printf("EXEC11\n");
		close (p[CUR][P_IN]);
		// printf("EXEC12\n");
		if (curr_cmd->has_heredoc == 2)//This might need to be on a different palce.
		{
			// printf("EXEC13\n");
			//printf("close (main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT]);%d\n", curr_cmd->heredoc_pipe[P_OUT]);
			close (curr_cmd->heredoc_pipe[P_OUT]);
			// printf("EXEC14\n");
		}
	}
	// printf("EXEC15\n");
	//printf("close (p[CUR][P_OUT]);%d\n", p[CUR][P_OUT]);
	close (p[CUR][P_OUT]);
	// printf("EXEC16\n");
	waitpid(id, &i, 0);
	// printf("EXEC17\n");
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	// printf("EXEC18\n");
	if (build_return >= 0)
		return (build_return);
	// printf("EXEC19\n");
	
	return (WEXITSTATUS(i));
}

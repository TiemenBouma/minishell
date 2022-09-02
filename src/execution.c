/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/09/02 17:51:01 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execve_error(char *path, int error, char *envpath)
{
	if (ft_strncmp(path, "./", 2) == 0 || envpath == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (error == ENOENT)
	{

			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": command not found\n", 2);
	}
	else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": execve error\n", 2);
		}
	exit (127);
}

int	exec(struct	s_main *main_struct)
{
	extern char **environ;
	int i = 0;
	int	build_return;
	int id = 1;
	int p[2][2];
	//sig_t	old_signal[2];
	struct s_cmd_info	*curr_cmd;
	char	*path;

	build_return = -1;
	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1

	while (i < main_struct->cmd_count)
	{
		i++;
		curr_cmd = &main_struct->cmd_struct_arr[i - 1];
		err_chk(pipe(p[CUR]), 1, "");
		
		//-------------------------------func singel command, is spesific buidlin--------------------------
		if (curr_cmd->exec.exec_line[0] && is_builtin(curr_cmd->exec.exec_line[0]) == EXIT_BUILD && main_struct->cmd_count == 1)
		{
			ft_exit(curr_cmd->exec.exec_line, 0);
			continue;
		}
		if (check_buildin_fork(curr_cmd) == 0 && curr_cmd->set_file_err == 0 &&  main_struct->cmd_count == 1)
		{
			build_return =  exec_builtin(curr_cmd, is_builtin(curr_cmd->exec.exec_line[0]));
		}
		//-------------------------------func singel command, is spesific buidlin--------------------------
		
		signal(SIGINT, sigint_handler_in_process);
		signal(SIGQUIT, sigquit_handler_in_process);
		if (check_buildin_fork(curr_cmd) == 1 || main_struct->cmd_count > 1)
		{
			id = fork();
		}
		err_chk(id, 1, "");
		if ((id == 0 && check_buildin_fork(curr_cmd) == 1) || (id == 0 && main_struct->cmd_count > 1))//Why is is_builtin in this if statment
		{
			// ---------------------------- make redir function? ---------------------------------
			if (curr_cmd->has_heredoc == 2)
			{
				err_chk(dup2(g_pipe_heredoc[P_OUT], S_IN), 2, "");//(curr_cmd->heredoc_pipe[P_OUT], S_IN), 2, "");
				close (g_pipe_heredoc[P_OUT]);//(curr_cmd->heredoc_pipe[P_OUT]);
			}
			else if (curr_cmd->has_infile == 2 || i == 1)
			{
				err_chk(dup2(curr_cmd->exec.fd_in, S_IN), 2, "");
			}
			else
			{
				err_chk(dup2(p[PREV][P_OUT], S_IN), 2, "");	
			}
			if (curr_cmd->exec.fd_out == 1 && main_struct->cmd_count != i)
			{
				err_chk(dup2(p[CUR][P_IN], S_OUT), 2, "");
			}
			else
			{
				err_chk(dup2(curr_cmd->exec.fd_out, S_OUT), 2, "");
			}
			close (p[CUR][P_OUT]);
			close (p[PREV][P_IN]);
			// ---------------------------- make redir function? ---------------------------------
			
			// ---------------------------- make exec function? ---------------------------------
			// if (is_builtin(curr_cmd->exec.exec_line[0]) < 7 && curr_cmd->set_file_err == 0 &&  main_struct->cmd_count < 1)
			// {
			// 	exec_builtin(curr_cmd, is_builtin(curr_cmd->exec.exec_line[0]));
			// 	exit(0);
			// }
			if (is_builtin(curr_cmd->exec.exec_line[0]) < 7 && curr_cmd->set_file_err == 0)
			{
				exec_builtin(curr_cmd, is_builtin(curr_cmd->exec.exec_line[0]));
				exit(0);
			}
			else if (curr_cmd->set_file_err == 0)
			{
				if (execve(curr_cmd->exec.exec_line[0], curr_cmd->exec.exec_line, make_arr_from_list(&main_struct->env_llist)) == -1)
				{
					if(curr_cmd->exec.exec_line[0] == NULL)
						exit(0);
					path = find_var_in_list(&main_struct->env_llist, "PATH");
					execve_error(curr_cmd->exec.exec_line[0], errno, path);
				}
			}
			else
				exit(126);
			// ---------------------------- make exec function? ---------------------------------
		}
		close (p[PREV][P_OUT]);
		close (p[CUR][P_IN]);
		if (i == 1 || curr_cmd->has_heredoc == 2)
			close (p[PREV][P_IN]);
	}
	close (p[CUR][P_OUT]);
	close (p[PREV][P_IN]);
	waitpid(id, &i, 0);
	while (wait(NULL) != -1);
	signals_handeler();
	if (build_return >= 0)
		return (build_return);
	return (WEXITSTATUS(i)); //check if exited with WIFSIGNALED or  WIFSTOPPED
}




/* TIEMENTS VERSION
	extern char **environ;
	int i = 0;
	int	build_return;
	int id = 1;
	int p[2][2];
	sig_t	old_signal[2];
	struct s_cmd_info	*curr_cmd;
	int child_n = 0;
	int status;

	build_return = -1;
	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1
	close (p[CUR][P_IN]);
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
			ft_exit(curr_cmd->exec.exec_line, 0); // NEEDS A token 
			//continue;
		}
		if (check_buildin_fork(curr_cmd) == 0 && curr_cmd->set_file_err == 0)
		{
			//printf("DEBUG1\n");
			build_return =  exec_builtin(curr_cmd, is_builtin(curr_cmd->exec.exec_line[0]));
		}
		else if (check_buildin_fork(curr_cmd) != 0)
			id = fork();//printf("DEBUG2\n");

		old_signal[0] = signal(SIGINT, sigint_handler_in_process);
		old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
		//printf("ID= %d\n", id);
		err_chk(id, 1, "");
		if (id == 0 && check_buildin_fork(curr_cmd) == 1)//Why is is_builtin in this if statment
		{
			// printf("EXEC1\n");
			if (curr_cmd->has_heredoc == 2)
			{
				 //printf("EXEC3\n");
				
				err_chk(dup2(curr_cmd->heredoc_pipe[P_OUT], S_IN), 2, "");
			}
			else if (curr_cmd->has_infile == 2 || i == 1)
			{
				//printf("EXEC2\n");
				
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
				// if (execve(curr_cmd->exec.exec_line[0], curr_cmd->exec.exec_line, make_arr_from_list(&main_struct->env_llist)) == -1)// check malloc of make_arr_func is freed
				// {
				// 	perror(curr_cmd->exec.exec_line[0]);
				// 	exit(127);	
				// }	
				// dprintf(2, "\nprocces: %d\n", i);
				if (execve(curr_cmd->exec.exec_line[0], curr_cmd->exec.exec_line, make_arr_from_list(&main_struct->env_llist)) == -1)
				{
					if(curr_cmd->exec.exec_line[0] == NULL)
						exit(0);
					execve_error(curr_cmd->exec.exec_line[0], errno);
					perror(curr_cmd->exec.exec_line[0]);
					exit(1);
					exit(127);	
				}
			}
			else
				exit(1);
		}

			//  printf("EXEC10\n");

			//printf("close (p[PREV][P_OUT]);%d\n", p[PREV][P_OUT]);
		close (p[PREV][P_OUT]);

		//printf("close (p[CUR][P_IN]);%d\n", p[CUR][P_IN]);
		//  printf("EXEC11\n");
		close (p[CUR][P_IN]);
		//  printf("EXEC12\n");
		if (curr_cmd->has_heredoc == 2)//This might need to be on a different palce.
		{
			//  printf("EXEC13\n");
			//printf("close (main_struct->cmd_struct_arr[i - 1].heredoc_pipe[P_OUT]);%d\n", curr_cmd->heredoc_pipe[P_OUT]);
			close (curr_cmd->heredoc_pipe[P_OUT]);
			//  printf("EXEC14\n");
		}
	}
	//  printf("EXEC15\n");
	//printf("close (p[CUR][P_OUT]);%d\n", p[CUR][P_OUT]);
	close (p[CUR][P_OUT]);
	//  printf("EXEC16\n");
	while (child_n < main_struct->cmd_count)
	{
		waitpid(-1, &status, 0);
		child_n++;
	}
	//  printf("EXEC17\n");
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	// printf("EXEC18\n");
	if (build_return >= 0)
		return (build_return);
	return (WEXITSTATUS(status)); //check if exited with WIFSIGNALED or  WIFSTOPPED 
*/
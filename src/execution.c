/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:53:02 by dkocob        #+#    #+#                 */
/*   Updated: 2022/08/17 21:19:50 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"

static int	heredoc(struct s_to_exec *exec, int (*p)[2][2], int i)
{
	char	**gnl;

	if (exec->heredoc)
	{
		err_chk(pipe((*p)[PREV]), 0, "");
		gnl = malloc (sizeof(char **) * 2);
		if (!gnl)
			exit(0);
		while (1)
		{
			if (get_next_line(0, gnl) == -1 || ft_strncmp (gnl[0], exec->heredoc,
					ft_strlen (exec->heredoc) + 1) == 0)
			{
				free(gnl[0]);
				free(gnl);
				break ;
			}
			write((*p)[PREV][P_IN], gnl[0], ft_strlen(gnl[0]));
			free(gnl[0]);
			write((*p)[PREV][P_IN], "\n", 1);
		}
		close((*p)[PREV][P_IN]);
		return (1);
	}
	return (0);
}

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
		id = fork();
		err_chk(id, 1, "");
		if (id == 0)
		{
			if (!main_struct->cmd_struct_arr->exec.heredoc)
				rr = 1;
			if (i == 1) //1st in
			{
				if (main_struct->cmd_struct_arr->has_heredoc != 1)
					err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
				else
				{
					write(2, "RR!1\n", 5);
					if (main_struct->cmd_struct_arr->has_heredoc == 1)
					{
						heredoc(&main_struct->cmd_struct_arr->exec, &p, i);
						err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
						// exit(0);
						// execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL);
					}
					else if (main_struct->cmd_struct_arr->exec.fd_in != 0)
						err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
					// if (main_struct->cmd_struct_arr->exec.fd_out != 1)
					// 	err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
				}
			}
			if (i != 1) // every mid in
			{
				if (main_struct->cmd_struct_arr->has_heredoc != 1)
					err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
				else
				{
					write(2, "RR!M\n", 5);
					if (main_struct->cmd_struct_arr->has_heredoc == 1)
					{
						heredoc(&main_struct->cmd_struct_arr->exec, &p, i);
						err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
						// exit(0);
						// execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL);
					}
				}
			}
			if (i != main_struct->cmd_count) //every out
			{
				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
			}
			if (i == main_struct->cmd_count) //end out
			{
				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
			}
			if (is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]))
			{
				exec_builtin(main_struct, main_struct->cmd_struct_arr[i - 1].exec.exec_line, is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
				exit(0);
			}
			execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL);
			exit (0);
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






// static int	heredoc(struct s_to_exec *exec, int (*p)[2][2], int i)
// {
// 	char	**gnl;

// 	if (exec->heredoc)
// 	{
// 		err_chk(pipe((*p)[PREV]), 0, "");
// 		gnl = malloc (sizeof(char **) * 2);
// 		if (!gnl)
// 			exit(0);
// 		while (1)
// 		{
// 			if (get_next_line(0, gnl) == -1 || ft_strncmp (gnl[0], exec->heredoc,
// 					ft_strlen (exec->heredoc) + 1) == 0)
// 			{
// 				free(gnl[0]);
// 				free(gnl);
// 				break ;
// 			}
// 			write((*p)[PREV][P_IN], gnl[0], ft_strlen(gnl[0]));
// 			free(gnl[0]);
// 			write((*p)[PREV][P_IN], "\n", 1);
// 		}
// 		close((*p)[PREV][P_IN]);
// 		return (1);
// 	}
// 	return (0);
// }

// int	exec(struct	s_main *main_struct)
// {
// 	int i = 0;

// 	int id = 0;
// 	int p[2][2];
// 	sig_t	old_signal[2];


// 	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1

	
// 	while (i < main_struct->cmd_count)
// 	{
// 		i++;
// 		err_chk(pipe(p[CUR]), 1, "");
// 		old_signal[0] = signal(SIGINT, sigint_handler_in_process);
// 		old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
// 		id = fork();
// 		err_chk(id, 1, "");
// 		if (id == 0)
// 		{
// 			if (i == 1) //1st
// 				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
// 			if (i != 1) // every
// 				err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
// 			if (i != main_struct->cmd_count) //every mid
// 				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
// 			if (i == main_struct->cmd_count) //end
// 				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
// 			if (is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]))
// 			{
// 				exec_builtin(main_struct, main_struct->cmd_struct_arr[i - 1].exec.exec_line, is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
// 				exit(0);
// 			}
// 			execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL); //why if command not found exit(0)?
// 		}
// 		close (p[PREV][P_OUT]);
// 		close (p[CUR][P_IN]);
// 	}
// 	close (p[CUR][P_OUT]);
// 	waitpid(id, &i, 0);
// 	signal(SIGINT, old_signal[0]);
// 	signal(SIGQUIT, old_signal[1]);
// 	return (WEXITSTATUS(i));
// }



// while (i < main_struct->cmd_count)
// 	{
// 		rr = 0;
// 		i++;
// 		err_chk(pipe(p[CUR]), 1, "");
// 		old_signal[0] = signal(SIGINT, sigint_handler_in_process);
// 		old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
// 		id = fork();
// 		err_chk(id, 1, "");
// 		if (id == 0)
// 		{
// 			if (main_struct->cmd_struct_arr->exec.fd_in == 0 && main_struct->cmd_struct_arr->exec.fd_out == 1 && !main_struct->cmd_struct_arr->exec.heredoc)
// 				rr = 1;
// 			if (i == 1) //1st
// 			{
// 				if (!rr)
// 					err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
// 				else
// 				{
// 					if (main_struct->cmd_struct_arr->exec.heredoc)
// 						heredoc(&main_struct->cmd_struct_arr->exec, &p);
// 					if (main_struct->cmd_struct_arr->exec.fd_in != 0)
// 						err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
// 					if (main_struct->cmd_struct_arr->exec.fd_out != 1)
// 						err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
// 				}
// 			}
// 			if (i != 1) // every
// 			{
// 				err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
// 			}
// 			if (i != main_struct->cmd_count) //every mid
// 			{
// 				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
// 			}
// 			if (i == main_struct->cmd_count) //end
// 			{
// 				err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
// 			}
			
// 			if (is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]))
// 			{
// 				exec_builtin(main_struct, main_struct->cmd_struct_arr[i - 1].exec.exec_line, is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
// 				exit(0);
// 			}
// 			execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL); //why if command not found exit(0)?
// 		}
// 		close (p[PREV][P_OUT]);
// 		close (p[CUR][P_IN]);
// 	}
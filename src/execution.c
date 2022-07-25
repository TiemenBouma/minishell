/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/07/25 15:14:26 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec(struct	s_cmd_lines	*d)
{
	int i = 0;
	int id = 0;
	int p[2][2];

	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1
	close(p[CUR][P_IN]);
	// err_chk(dup2(d->cmd_info[i].pipe_cmd.in , STD_IN), 1, "");
	// err_chk(dup2(STD_IN, STD_IN), 1, "");
	// close(p[CUR][P_IN]);
	
	while (i < d->cmd_count + 1)
	{
		i++;
		err_chk(pipe(p[CUR]), 1, ""); //CUR = 0
		id = fork(); // 4 pipe ends , 8 ptrs
		err_chk(id, 1, "");
		if (id == 0)
		{
			close(p[CUR][P_OUT]);
			//fd: 
			if (i != 1 && i < d->cmd_count + 1)
			{
				err_chk(dup2(p[PREV][P_OUT], STD_IN), 1, "");
				err_chk(dup2(p[CUR][P_IN], STD_OUT), 1, "");
			}
			else if (i != 1)
			{
				err_chk(dup2(p[PREV][P_OUT], STD_IN), 1, "");
				err_chk(dup2(d->cmd_info[i - 1].pipe_cmd.fd_out , STD_OUT), 1, "");
			}
			// close (p[CUR][P_IN]);
			execve(d->cmd_info[i - 1].pipe_cmd.exec_line[0], d->cmd_info[i - 1].pipe_cmd.exec_line, NULL);
		}
		// if (i > 1)
		close (p[PREV][P_OUT]);
		close (p[CUR][P_IN]);
	}
	waitpid(id, &i, 0);
	exit (WEXITSTATUS(i));
}



// void child(int i, int id, char **cmd, int fdin, int fdout)
// {
// 	if (id == 0)
// 	{
// 		// if (i == 1)
// 		// {
// 		// 	err_chk(dup2(fdin, STD_IN), 1, "");
// 		// 	err_chk(dup2(fdout, STD_OUT), 1, "");
// 		// }
// 		// else if (i < argc - 3)
// 		// {
// 		err_chk(dup2(fdin, STD_IN), 1, ""); //i1  p1 OUT -> STD_IN
// 		err_chk(dup2(fdout, STD_OUT), 1, ""); //i1 STD_OUT -> p0 IN
// 		// }
// 		// else
// 		// {
// 		// 	close(pipe[PREV][P_IN]);
// 		// 	err_chk(dup2(fdout, STD_OUT), 1, "");
// 		// 	err_chk(dup2(fdin, STD_IN), 1, "");
// 		// }
// 		close (fdout); //i1 p0 cI
// 		execve(cmd[0], cmd, NULL);
// 	}
// }

// int	execution(int *fdin, int *fdout, char ***cmdtoexec, int cmdcount)
// {
// 	int i = 0;
// 	int id;
// 	int pipe[2][2];
	

// 	err_chk(pipe(pipe[CUR]), 0, "");
// 	err_chk(dup2(fdin[i], pipe[CUR][PIPE_IN]), 1, "");
// 	while (i < cmdcount)
// 	{
// 		i++;
// 		err_chk(pipe(pipe[CUR]), 1, ""); //i1 p0
// 		id = fork();
// 		err_chk(id, 1, "");
// 		if (id == 0)
// 		{
// 			close(pipe[CUR][PIPE_OUT]); // i1 p0 cO
// 			child(id, cmdtoexec[i], pipe[PREV][P_OUT], pipe[CUR][P_IN]);
// 			if (i == 1)
// 			{
// 				child(id, cmdtoexec[i], pipe[PREV][P_OUT], pipe[CUR][P_IN]);
// 			}
// 			if (i == cmdcount)
// 			{
// 				child(id, cmdtoexec[i], pipe[PREV][P_OUT], fdend);
				
// 			}
// 		}
// 		if (i > 1)
// 			close (pipe[PREV][P_OUT]);
// 	}
// 	waitpid(id, &i, 0);
// 	exit (WEXITSTATUS(i));
// }

// # define PIPE_OUT 0
// # define PIPE_IN 1
// # define STD_OUT 1
// # define STD_IN 0
// # define CUR CUR
// # define PREV PREV
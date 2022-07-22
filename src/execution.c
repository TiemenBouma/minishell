/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:53:02 by dkocob        #+#    #+#                 */
/*   Updated: 2022/07/22 14:51:49 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void child(int i, int id, char **cmd, int fdin, int fdout)
{
	if (id == 0)
	{
		// if (i == 1)
		// {
		// 	err_chk(dup2(fdin, S_IN), 1, "");
		// 	err_chk(dup2(fdout, STD_OUT), 1, "");
		// }
		// else if (i < argc - 3)
		// {
		err_chk(dup2(fdin, STD_IN), 1, ""); //i1  p1 OUT -> S_IN
		err_chk(dup2(fdout, STD_OUT), 1, ""); //i1 S_OUT -> p0 IN
		// }
		// else
		// {
		// 	close(pipe[PREV][IN]);
		// 	err_chk(dup2(fdout, STD_OUT), 1, "");
		// 	err_chk(dup2(fdin, STD_IN), 1, "");
		// }
		close (fdout); //i1 p0 cI
		execve(cmd[0], cmd, NULL);
	}
}

int	execution(int *fdin, int *fdout, char ***cmdtoexec, int cmdcount)
{
	int i = 0;
	int id;
	int pipe[2][2];
	

	err_chk(pipe(pipe[CUR]), 0, "");
	err_chk(dup2(fdin[i], pipe[CUR][PIPE_IN]), 1, "");
	while (i < cmdcount)
	{
		i++;
		err_chk(pipe(pipe[CUR]), 1, ""); //i1 p0
		id = fork();
		err_chk(id, 1, "");
		if (id == 0)
		{
			close(pipe[CUR][PIPE_OUT]); // i1 p0 cO
			child(id, cmdtoexec[i], pipe[PREV][OUT], pipe[CUR][IN]);
			if (i == 1)
			{
				child(id, cmdtoexec[i], pipe[PREV][OUT], pipe[CUR][IN]);
			}
			if (i == cmdcount)
			{
				child(id, cmdtoexec[i], pipe[PREV][OUT], fdend);
				
			}
		}
		if (i > 1)
			close (pipe[PREV][OUT]);
	}
	waitpid(id, &i, 0);
	exit (WEXITSTATUS(i));
}

# define PIPE_OUT 0
# define PIPE_IN 1
# define STD_OUT 1
# define STD_IN 0
# define CUR (i + 1) % 2
# define PREV i % 2
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:53:02 by dkocob        #+#    #+#                 */
/*   Updated: 2022/07/18 20:50:26 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution(int *fdin, int *fdout, char ***cmdtoexec, char **envp)
{
	
	i = 0;
	while (i < argc - 3)
	{
		i++;
		err_chk(pipe(pipe[(i + 1) % 2]), 1, "");
		id = fork();
		err_chk(id, 1, "");
		if (id == 0)
		{
			close(pipe[(i + 1) % 2][OUT]);
			close(pipe[i % 2][IN]);
			err_chk(dup2(fd2, S_OUT), 1, "");
			err_chk(dup2(pipe[i % 2][OUT], S_IN), 1, "");
			close (pipe[(i + 1) % 2][IN]);
			execve(cmd1[0], cmd1, NULL);
		}
		close (pipe[i % 2][OUT]);
		close (pipe[(i + 1) % 2][IN]);
	}
	waitpid(id, &i, 0);
	exit (WEXITSTATUS(i));
}

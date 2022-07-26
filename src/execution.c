/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/07/26 11:06:20 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec(struct	s_cmd_lines	*d)
{
	int i = 0;
	//int in1 = 0;
	//int out1 = 1;
	int id = 0;
	int p[2][2];
	// char ***testp;

	// //d->cmd_count = 2;
	// testp = malloc(sizeof(char***) * 5);
	// testp[0] = ft_split ("/bin/ls", ' ');
	// // testp[1] = ft_split ("usr/bin/wc -l", ' ');
	// testp[1] = ft_split ("/bin/cat -e", ' ');
	// testp[2] = ft_split ("/bin/ls", ' ');
	// testp[3] = ft_split ("/bin/cat", ' ');
	// testp[4] = NULL;

	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1


	
	while (i < d->cmd_count)
	{
		i++;
		err_chk(pipe(p[CUR]), 1, "");
		id = fork();
		err_chk(id, 1, "");
		if (id == 0)
		{
			if (i == 1) //1st
				err_chk(dup2(d->cmd_info[i - 1].pipe_cmd.fd_in, S_IN), 1, "");
			if (i != 1) // every
				err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
			if (i != d->cmd_count) //every mid
				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
			if (i == d->cmd_count) //end
				err_chk(dup2(d->cmd_info[i - 1].pipe_cmd.fd_out, S_OUT), 1, "");
			execve(d->cmd_info[i - 1].pipe_cmd.exec_line[0], d->cmd_info[i - 1].pipe_cmd.exec_line, NULL);
		}
		close (p[PREV][P_OUT]);
		close (p[CUR][P_IN]);
	}
	close (p[CUR][P_OUT]);
	waitpid(id, &i, 0);
	exit (WEXITSTATUS(i));
}

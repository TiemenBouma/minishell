/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/08 14:48:07 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec(struct	s_main *main_struct)
{
	int i = 0;

	int id = 0;
	int p[2][2];


	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1


	
	while (i < main_struct->cmd_count)
	{
		i++;
		err_chk(pipe(p[CUR]), 1, "");
		id = fork();
		err_chk(id, 1, "");
		if (id == 0)
		{
			if (i == 1) //1st
				err_chk(dup2(main_struct->curr_cmd_info[i - 1].exec.fd_in, S_IN), 1, "");
			if (i != 1) // every
				err_chk(dup2(p[PREV][P_OUT], S_IN), 1, "");
			if (i != main_struct->cmd_count) //every mid
				err_chk(dup2(p[CUR][P_IN], S_OUT), 1, "");
			if (i == main_struct->cmd_count) //end
				err_chk(dup2(main_struct->curr_cmd_info[i - 1].exec.fd_out, S_OUT), 1, "");
			if (is_builtin(main_struct->curr_cmd_info[i - 1].exec.exec_line[0]))
			{
				exec_builtin(main_struct, main_struct->curr_cmd_info[i - 1].exec.exec_line, is_builtin(main_struct->curr_cmd_info[i - 1].exec.exec_line[0]));
				exit(0);
			}
			execve(main_struct->curr_cmd_info[i - 1].exec.exec_line[0], main_struct->curr_cmd_info[i - 1].exec.exec_line, NULL); //why if command not found exit(0)?
		}
		close (p[PREV][P_OUT]);
		close (p[CUR][P_IN]);
	}
	close (p[CUR][P_OUT]);
	waitpid(id, &i, 0);
	return (WEXITSTATUS(i));
}

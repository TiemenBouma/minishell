/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:53:02 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/15 15:00:24 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"


int	pipe_redir(struct s_main *main_struct, int (*p)[2][2], int i)
{
	if (i == 1 && !main_struct->cmd_struct_arr->heredoc) //1st
	{
		//printf("TEST1\n");
		err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_in, S_IN), 1, "");
	}
	if (i != 1 || (i == 1 && main_struct->cmd_struct_arr->heredoc)) // every Other
	{
		//printf("TEST2\n");
		err_chk(dup2((*p)[PREV][P_OUT], S_IN), 1, "");
	}
	if (i != main_struct->cmd_count) //every mid
	{
		//printf("TEST3\n");
		err_chk(dup2((*p)[CUR][P_IN], S_OUT), 1, "");
	}
	if (i == main_struct->cmd_count) //end
	{
		//printf("TEST4\n");
		err_chk(dup2(main_struct->cmd_struct_arr[i - 1].exec.fd_out, S_OUT), 1, "");
	}
	return (0);
}

static int	heredoc(struct s_main *main_struct, int (*p)[2][2])
{
	char	**gnl;

	if (main_struct->cmd_struct_arr->heredoc)
	{
		printf("stopWORD:%s\n", main_struct->cmd_struct_arr->heredoc);
		err_chk(pipe((*p)[1]), 0, "");
		gnl = malloc (sizeof(char **) * 2);
		if (!gnl)
			exit(0);
		while (1)
		{
			if (get_next_line(0, gnl) == -1 || ft_strncmp (gnl[0], main_struct->cmd_struct_arr->heredoc,
					ft_strlen (main_struct->cmd_struct_arr->heredoc) + 1) == 0)
			{
				free(gnl[0]);
				free(gnl);
				break ;
			}
			write((*p)[1][P_IN], gnl[0], ft_strlen(gnl[0]));
			free(gnl[0]);
			write((*p)[1][P_IN], "\n", 1);
		}
		close((*p)[1][P_IN]);
		return (1);
	}
	return (0);
}

int	exec(struct	s_main *main_struct)
{
	int	saved_std_in;
	int	saved_std_out;
	int i = 0;
	int status;
	//int id = 1;
	int p[2][2];
	sig_t	old_signal[2];

	if (main_struct->has_herdoc == 1)
	{
		printf("DEBUG HERDOC\n");
		heredoc(main_struct, &p);
	}
	if (main_struct->cmd_struct_arr->heredoc)
		err_chk(pipe(p[CUR]), 1, ""); //CUR = 1
	if (!main_struct->cmd_struct_arr[i].exec.exec_line[0])
		return (1); //make redir and continue
	if (ft_strncmp(main_struct->cmd_struct_arr[i].exec.exec_line[0], "exit", 4 + 1) == 0 && main_struct->cmd_count == 1)
		exit(0);// Probably need function to check what exit status to use. maybe need other exit code
	while (i < main_struct->cmd_count)
	{
		saved_std_in = dup(STD_IN);
		saved_std_out= dup(STD_OUT);
		i++;
		err_chk(pipe(p[CUR]), 1, "");
		old_signal[0] = signal(SIGINT, sigint_handler_in_process);
		old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
		if (!is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]))//if (check_buildin_fork(&main_struct->cmd_struct_arr[i - 1]))
		{ // NOT BUILDINS
			main_struct->pid_child = fork();
			//err_chk(id, 1, "");
			if (main_struct->pid_child == 0)
			{
				pipe_redir(main_struct, &p, i);
				execve(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0], main_struct->cmd_struct_arr[i - 1].exec.exec_line, NULL); //why if command not found exit(0)?
				exit (0);//For wrong commands We need to handel wrong commands dfferently
			}
		}
		else //BUILDIN
		{ //if buidlin is executed with redirections, they need to be chanced back
			if (check_buildin_stdinout(&main_struct->cmd_struct_arr[i - 1]))
			{
				pipe_redir(main_struct, &p, i);
				exec_builtin(main_struct, main_struct->cmd_struct_arr[i - 1].exec.exec_line, is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
				dup2(saved_std_in, STD_IN);
				dup2(saved_std_in, STD_OUT);
				close(saved_std_in);
				close(saved_std_out);

					
				//exit(0);
			}
			else //NO STDIN STDOUT needed. Are stdin and out 0 and 1? Do they need to be 0 and 1?
			{
				exec_builtin(main_struct, main_struct->cmd_struct_arr[i - 1].exec.exec_line, is_builtin(main_struct->cmd_struct_arr[i - 1].exec.exec_line[0]));
				//exit(0);
			}
		}


		if (main_struct->pid_child == 0)
			ft_putstr_fd("STILL IN CHILD, WRONG\n", 2);
		close (p[PREV][P_OUT]);
		close (p[CUR][P_IN]);
	}
	close (p[CUR][P_OUT]);
	waitpid(main_struct->pid_child, &status, 0);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	return (WEXITSTATUS(status));
}

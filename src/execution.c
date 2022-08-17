/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:53:02 by dkocob        #+#    #+#                 */
/*   Updated: 2022/08/17 15:05:46 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_next_line.h"


int	pipe_redir(struct s_cmd_info *cmd_struct, int (*p)[2][2], int i)
{
	if (i == 1)// && !cmd_struct->heredoc) //1st
	{
		//printf("TEST1\n");
		err_chk(dup2(cmd_struct->exec.fd_in, S_IN), 1, "");
	}
	if (i != 1 || (i == 1 && cmd_struct->has_heredoc > 0)) // every Other
	{
		//printf("TEST2\n");
		err_chk(dup2((*p)[PREV][P_OUT], S_IN), 1, "");
	}
	if (i != cmd_struct->exec.cmd_count) //every mid
	{
		//printf("TEST3\n");
		err_chk(dup2((*p)[CUR][P_IN], S_OUT), 1, "");
	}
	if (i == cmd_struct->exec.cmd_count) //end
	{
		//printf("TEST4\n");
		err_chk(dup2(cmd_struct->exec.fd_out, S_OUT), 1, "");
	}
	return (0);
}

static int	heredoc(struct s_cmd_info *cmd_struct, int (*p)[2][2])
{
	char	**gnl;

	//printf("\nIN HEREDOC\n\n");
	if (cmd_struct->heredoc)
	{
		//printf("stopWORD:%s\n", cmd_struct->heredoc);
		err_chk(pipe((*p)[1]), 0, "");
		gnl = malloc (sizeof(char **) * 2);
		if (!gnl)
			exit(0);
		while (1)
		{
			if (get_next_line(0, gnl) == -1 || ft_strncmp(gnl[0], cmd_struct->heredoc,
					ft_strlen (cmd_struct->heredoc) + 1) == 0)
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

int exec2(struct s_cmd_info *cmd_struct, int saved_in_out[2], int (*p)[2][2], sig_t old_signal[2], int i)//(main_struct->cmd_struct_arr[i - 1], &saved_in_out, &p, &old_signal)
{
	if (cmd_struct->has_heredoc > 0)
	{
		//pipe_redir(cmd_struct, p, i);
		heredoc(cmd_struct, p);
	}
	if (cmd_struct->has_heredoc != 0)
		err_chk(pipe((*p)[CUR]), 1, ""); //CUR = 1
	saved_in_out[0] = dup(STD_IN);
	saved_in_out[1] = dup(STD_OUT);
	//err_chk(pipe((*p)[CUR]), 1, "");
	old_signal[0] = signal(SIGINT, sigint_handler_in_process);
	old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
	//printf("EXEC START\n");
	//printf("%s\n", cmd_struct->exec.exec_line[0]);
	if (!is_builtin(cmd_struct->exec.exec_line[0]))//if (check_buildin_fork(&main_struct->cmd_struct_arr[i - 1]))
	{ // NOT BUILDINS
		//printf("IN SYSTEM FUNC\n");
		cmd_struct->pid_child = fork();
		//err_chk(id, 1, "");
		if (cmd_struct->pid_child == 0)
		{
		//	printf("SYSTEM FUNC CHILD\n");
			pipe_redir(cmd_struct, p, i);
			execve(cmd_struct->exec.exec_line[0], cmd_struct->exec.exec_line, NULL); //why if command not found exit(0)?
			exit (0);//For wrong commands We need to handel wrong commands dfferently
		}
	}
	else //BUILDIN
	{ //if buidlin is executed with redirections, they need to be chanced back
		if (check_buildin_stdinout(cmd_struct))
		{
			pipe_redir(cmd_struct, p, i);
			exec_builtin(cmd_struct, is_builtin(cmd_struct->exec.exec_line[0]));
			dup2(saved_in_out[0], STD_IN);
			dup2(saved_in_out[1], STD_OUT);
			close(saved_in_out[0]);
			close(saved_in_out[1]);

				
			//exit(0);
		}
		else //NO STDIN STDOUT needed. Are stdin and out 0 and 1? Do they need to be 0 and 1?
		{
			exec_builtin(cmd_struct, is_builtin(cmd_struct->exec.exec_line[0]));
			//exit(0);
		}
	}


	if (cmd_struct->pid_child == 0)
		ft_putstr_fd("STILL IN CHILD, WRONG\n", 2);
	// close ((*p)[PREV][P_OUT]);
	// close ((*p)[CUR][P_IN]);
	return (0);
}

int	exec(struct	s_main *main_struct)
{
	int	saved_in_out[2];
	int i = 0;
	int status;
	//int id = 1;
	int p[2][2];
	sig_t	old_signal[2];

	// if (main_struct->has_heredoc == 1)
	// {
	// 	heredoc(main_struct, &p);
	// }
	// if (main_struct->cmd_struct_arr->heredoc)
	// 	err_chk(pipe(p[CUR]), 1, ""); //CUR = 1
	if (!main_struct->cmd_struct_arr[i].exec.exec_line[0] && main_struct->cmd_struct_arr[i].has_heredoc == 0)
	{
		//printf("Will renturn\n");
		return (1); //make redir and continue
	}
	if (main_struct->cmd_struct_arr[i].exec.exec_line[0] && ft_strncmp(main_struct->cmd_struct_arr[i].exec.exec_line[0], "exit", 4 + 1) == 0 && main_struct->cmd_count == 1)
		exit(0);// Probably need function to check what exit status to use. maybe need other exit code
	while (i < main_struct->cmd_count)
	{
		i++;
		exec2(&main_struct->cmd_struct_arr[i - 1], saved_in_out, &p, old_signal, i);
		
	}
	close (p[CUR][P_OUT]);
	waitpid(main_struct->cmd_struct_arr[main_struct->cmd_count - 1].pid_child, &status, 0);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	return (WEXITSTATUS(status));
}

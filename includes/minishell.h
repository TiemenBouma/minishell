/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 16:02:44 by tiemen        #+#    #+#                 */
/*   Updated: 2022/07/14 14:08:33 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERR_FILE		"Infile or outfile error"
# define ERR_FORK		"Fork error"
# define ERR_INPUT		"Invalid number of arguments"
# define ERR_PIPE		"Pipe error"
# define ERR_CMD		"command not found"
# define ERR_MALLOC		"Malloc error"
# define ERR_DUP		"Dup2 error"
# define ERR_PROCCES	"Procces error"
# define ERR_EXEC		"Execve error"
# define ERR_PATH		"Path error"

typedef struct s_p
{
	pid_t	pid_child;
	pid_t	wait;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*cmd_path;
	char	**cmd;
	int		argc;
	char	**argv;
	int		child_n;
	char	**root_paths;
}t_p;

//UTILS
void	error_msg(char *msg, int err);
void	perror_msg(char *msg, int err);
int free_stuff(char *str);

//PATH COMMAND
char	**find_path(char **envp);
char	*find_cmd_path(char **root_paths, char *cmd);


#endif
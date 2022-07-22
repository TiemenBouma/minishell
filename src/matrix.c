/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/17 16:09:00 by dkocob        #+#    #+#                 */
/*   Updated: 2022/07/22 17:04:20 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	get_arg_stack(struct s_data *d)
// {
// 	struct s_line	*new;
// 	struct s_line	*cur;
// 	char			*line;
// 	int				i;

// 	i = 0;
// 	cur = malloc(sizeof(struct s_line));
// 	if (!cur || d->m.fd < 1)
// 		exit (0);
// 	while (get_next_line(d->m.fd, &line))
// 	{
// 		cur->line = line;
// 		if (i == 0)
// 			d->m.lhead = cur;
// 		new = malloc(sizeof(struct s_line));
// 		if (!new || d->m.fd < 1)
// 			exit (0);
// 		cur->next = new;
// 		cur = new;
// 		i++;
// 	}
// 	new->next = NULL;
// 	d->m.szy = i;
// }

//expantion of variables before matrix
//{ is there variables?
// -> expand them
// -> form new tokens array
//}
// anylising inputs and ouputs redirections
// {

// return matrix.redir = malloc(sizeof(result) * ammountofpipes);
// }


// char	**get_paths(char **envp)
// {
// 	int		i;
// 	char	**paths;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 		{
// 			paths = ft_split(envp[i] + 5, ':');
// 			if (!paths)
// 				exit (0);
// 			return (paths);
// 		}
// 		i++;
// 		paths = NULL;
// 	}
// 	return (0);
// }

// void	get_cmd(struct s_d *d, char *cmd, int argc)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	d->cmd1 = ft_split(cmd, ' ');
// 	if (!d->cmd1 || !d->cmd1[0])
// 		exit (0);
// 	if (access(d->cmd1[0], X_OK) > -1)
// 		return ;
// 	d->cmd1[0] = ft_sjf("/", d->cmd1[0], 0);
// 	err_chk(0, 0, d->cmd1[0]);
// 	tmp = ft_sjf("", d->cmd1[0], 2);
// 	err_chk(0, 0, tmp);
// 	while (d->paths[i])
// 	{
// 		d->cmd1[0] = ft_sjf(d->paths[i], tmp, 0);
// 		err_chk(0, 0, d->cmd1[0]);
// 		if (access(d->cmd1[0], X_OK) > -1)
// 			break ;
// 		free (d->cmd1[0]);
// 		i++;
// 	}
// 	free (tmp);
// 	if (d->i == argc - 3 && access(d->cmd1[0], X_OK) == -1)
// 		err_chk(-1, 0, "");
// }

// static int	heredoc(char **argv, struct s_d *d)
// {
// 	char	**gnl;

// 	if (ft_strncmp(argv[1], "here_doc", 8 + 1) == 0)
// 	{
// 		err_chk(pipe(d->pipe[0]), 0, "");
// 		gnl = malloc (sizeof(char **) * 2);
// 		if (!gnl)
// 			exit(0);
// 		while (1)
// 		{
// 			if (get_next_line(0, gnl) == -1 || ft_strncmp (gnl[0], argv[2],
// 					ft_strlen (argv[2]) + 1) == 0)
// 			{
// 				free(gnl[0]);
// 				free(gnl);
// 				break ;
// 			}
// 			write(d->pipe[0][IN], gnl[0], ft_strlen(gnl[0]));
// 			free(gnl[0]);
// 			write(d->pipe[0][IN], "\n", 1);
// 		}
// 		close(d->pipe[0][IN]);
// 		return (1);
// 	}
// 	return (0);
// }


// void sort_tokens_for_execve(struct s_data d)
// {
// 	int ammountofpipes = 10; //result after expantion of variables
// 	struct s_matrix matrix;
	
// 	matrix.result = malloc(sizeof(result) * ammountofpipes);
// 	return (result);
// }
// goes to execution.c

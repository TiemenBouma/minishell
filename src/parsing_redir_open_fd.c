/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_redir_open_fd.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 10:32:41 by tbouma        #+#    #+#                 */
/*   Updated: 2022/09/13 15:38:58 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit_redir(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

int	open_fd_in(struct s_cmd_info *cmd_struct)
{
	if (cmd_struct->fd_in != 0)
		close(cmd_struct->fd_in);
	cmd_struct->fd_in = open(cmd_struct->infile, O_RDONLY);
	if (cmd_struct->fd_in < 0)
		error_exit_redir(cmd_struct->infile);
	return (1);
}

int	open_fd_out(struct s_cmd_info *cmd_struct)
{
	if (cmd_struct->has_outfile >= 1)
		cmd_struct->fd_out = open(cmd_struct->outfile, O_RDONLY
				| O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd_struct->fd_out < 0)
		error_exit_redir(cmd_struct->outfile);
	return (1);
}

int	open_fd_out_append(struct s_cmd_info *cmd_struct)
{
	if (cmd_struct->has_appendfile >= 1)
		cmd_struct->fd_out = open(cmd_struct->appendfile, O_RDONLY
				| O_CREAT | O_RDWR | O_APPEND, 0644);
	if (cmd_struct->fd_out < 0)
		error_exit_redir(cmd_struct->appendfile);
	return (1);
}

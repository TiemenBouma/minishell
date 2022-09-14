/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:30:01 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 14:30:13 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	look_for_redir(struct s_cmd_info *cmd_struct);

int	redir_check(struct s_cmd_info *cmd_struct)
{
	if (look_for_redir(cmd_struct))
		return (1);
	if (cmd_struct->has_heredoc == 2 && cmd_struct->fd_in != 0)
		close(cmd_struct->fd_in);
	if (cmd_struct->has_infile == 2 && cmd_struct->has_heredoc > 0)
		close(cmd_struct->heredoc_pipe[0]);
	return (1);
}

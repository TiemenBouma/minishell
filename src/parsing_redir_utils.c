/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_redir_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 10:36:55 by tbouma        #+#    #+#                 */
/*   Updated: 2022/09/13 11:51:59 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_arrow_sign(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (SMALLER);
	if (ft_strncmp(str, ">", 2) == 0)
		return (GREATER);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (HEREDOC);
	return (0);
}

int	is_special_c_redir(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (1);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "|", 2) == 0)
		return (1);
	else
		return (0);
}

void	set_redir_error(struct s_cmd_info *cmd_struct, char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	write(2, "'\n", 2);
	cmd_struct->err_syntax = 1;
}

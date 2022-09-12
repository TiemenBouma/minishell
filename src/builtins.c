/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:09:35 by dkocob            #+#    #+#             */
/*   Updated: 2022/09/12 14:54:06 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char	*s)
{
	if (!s)
		return (11);
	else if (ft_strncmp(s, "cd", 11 + 1) == 0)
		return (CD_BUILD);
	else if (ft_strncmp(s, "export", 6 + 1) == 0)
		return (EXPORT_BUILD);
	else if (ft_strncmp(s, "unset", 5 + 1) == 0)
		return (UNSET_BUILD);
	else if (ft_strncmp(s, "echo", 9 + 1) == 0)
		return (ECHO_BUILD);
	else if (ft_strncmp(s, "pwd", 8 + 1) == 0)
		return (PWD_BUILD);
	else if (ft_strncmp(s, "env", 3 + 1) == 0)
		return (ENV_BUILD);
	else if (ft_strncmp(s, "exit", 4 + 1) == 0)
		return (EXIT_BUILD);
	return (10);
}

int	exec_builtin(struct s_main *m_s,
struct	s_cmd_info *cmd_struct, int build_n)
{
	if (build_n == CD_BUILD)
		return (ft_cd(&cmd_struct->env_llist, &cmd_struct->exec_line));
	else if (build_n == EXPORT_BUILD)
		return (ft_export(&cmd_struct->env_llist, cmd_struct->exec_line));
	else if (build_n == UNSET_BUILD)
		return (ft_unset(&cmd_struct->env_llist, cmd_struct->exec_line));
	else if (build_n == ECHO_BUILD)
		ft_echo(cmd_struct->exec_line);
	else if (build_n == PWD_BUILD)
		ft_pwd(&cmd_struct->env_llist);
	else if (build_n == ENV_BUILD)
		ft_env(&cmd_struct->env_llist);
	else if (build_n == EXIT_BUILD)
		ft_exit(cmd_struct->exec_line, 1, m_s);
	return (0);
}

int	check_buildin_fork(struct s_cmd_info *cmd_struct)
{
	int	checker;

	checker = is_builtin(cmd_struct->exec_line[0]);
	if (checker == CD_BUILD || checker == EXPORT_BUILD
		|| checker == UNSET_BUILD)
		return (0);
	else
		return (1);
}

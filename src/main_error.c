/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:52:24 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/26 11:22:56 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	basic_error_handeling(struct s_main *m_s)
{
	int	i;

	i = 0;
	if (m_s->all_tokens[0] == NULL)
		return (1);
	while (m_s->all_tokens[i] != NULL)
		i++;
	if (ft_strcmp(m_s->all_tokens[i - 1], "|") == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		m_s->oxs = 258;
		return (1);
	}
	return (0);
}

int	check_error(struct s_main *m_s)
{
	int	i;

	i = 0;
	while (i < m_s->cmd_count)
	{
		if (m_s->c_s_arr[i].err_syntax > 0 || m_s->c_s_arr[i].set_file_err > 0)
		{
			m_s->err = 1;
			m_s->oxs = 258;
			free_struct(m_s);
			return (1);
		}
		i++;
	}
	return (0);
}

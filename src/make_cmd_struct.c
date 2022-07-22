/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:48:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/22 11:57:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

make_cmd_structs(struct s_cmd_lines *cmd_lines)
{
	int i;
	
	while (cmd_lines->cmd_lines[cmd_lines->cmd_count])
		cmd_lines->cmd_count++;
	cmd_lines->cmd_info = malloc(sizeof(struct s_cmd_info) * cmd_lines->cmd_count);
	while (i < cmd_lines->cmd_count)
	{
		
	}
}
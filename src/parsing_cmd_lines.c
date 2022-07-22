/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:45:51 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/22 11:31:42 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_cmd_line_count(char **tokens, int cmd_count)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i][0] == '|')
			cmd_count++;
		i++;
	}
	return (cmd_count);
}

static int	get_cmd_len(char **tokens, int current_token)
{
	int len;

	len = 0;
	while (tokens[current_token] && tokens[current_token][0] != '|')
	{
		len++;
		current_token++;
	}
	return (len);
}

static int	make_cmd(char **cmd_line, char **tokens, int current_token, int cmd_len)
{
	int	i;
	int	str_len;

	i = 0;
	while (i < cmd_len)
	{
		str_len = ft_strlen(tokens[current_token + i]);
		cmd_line[i] = malloc(sizeof(char) * (str_len + 1));
		ft_strlcpy(cmd_line[i], tokens[current_token + i], str_len + 1);
		i++;
	}
	return (0);
}

static int	get_cmds(char **tokens, char ***cmds, int cmd_lines)
{
	int	current_token;
	int cmd_len;
	int	i;

	i = 0;
	current_token = 0;
	while (i < cmd_lines)
	{
		cmd_len = get_cmd_len(tokens, current_token);
		cmds[i] = malloc(sizeof(char *) * (cmd_len + 1));
		make_cmd(cmds[i], tokens, current_token, cmd_len);
		current_token += cmd_len;
		current_token++;
		i++;
	}
	return (0);
}

char	***make_cmd_lines(char **tokens)
{
	int cmd_lines;
	char	***cmds;

	cmd_lines = 1;
	cmd_lines = get_cmd_line_count(tokens, cmd_lines);	
	cmds = malloc(sizeof(char **) * (cmd_lines + 1));
	cmds[cmd_lines] = NULL;
	
	get_cmds(tokens, cmds, cmd_lines);
	return (cmds);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:45:51 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/19 09:27:36 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	**g_pipe_heredoc;

static int	get_cmd_line_count(char **all_tokens, int cmd_count)
{
	int	i;

	i = 0;
	if (all_tokens == NULL)
		exit (printf("all_tokens not exits!\n"));
	while (all_tokens[i] != NULL)
	{
		if (all_tokens[i][0] == '|')
			cmd_count++;
		i++;
	}
	return (cmd_count);
}

static int	get_cmd_len(char **all_tokens, int current_token)
{
	int	len;

	len = 0;
	while (all_tokens[current_token] && all_tokens[current_token][0] != '|')
	{
		len++;
		current_token++;
	}
	return (len);
}

static int	make_cmd(char **cmd_line, char **all_tokens,
	int current_token, int cmd_len)
{
	int	i;
	int	str_len;

	i = 0;
	while (i < cmd_len)
	{
		str_len = ft_strlen(all_tokens[current_token + i]);
		cmd_line[i] = malloc(sizeof(char) * (str_len + 1));
		if (cmd_line[i] == NULL)
			exit(1);
		cmd_line[i][str_len] = '\0';
		ft_strlcpy(cmd_line[i], all_tokens[current_token + i], str_len + 1);
		i++;
	}
	return (0);
}

static int	get_cmds(char **all_tokens, char ***cmds, int cmd_lines)
{
	int	current_token;
	int	cmd_len;
	int	i;

	i = 0;
	current_token = 0;
	while (i < cmd_lines)
	{
		cmd_len = get_cmd_len(all_tokens, current_token);
		cmds[i] = malloc(sizeof(char *) * (cmd_len + 1));
		if (cmds[i] == NULL)
			exit (1);
		cmds[i][cmd_len] = NULL;
		make_cmd(cmds[i], all_tokens, current_token, cmd_len);
		current_token += cmd_len;
		current_token++;
		i++;
	}
	return (0);
}

char	***make_cmd_lines(char **all_tokens)
{
	int		cmd_lines;
	char	***cmds;
	int		i;

	i = 0;
	cmd_lines = 1;
	cmd_lines = get_cmd_line_count(all_tokens, cmd_lines);
	cmds = malloc(sizeof(char **) * (cmd_lines + 1));
	if (cmds == NULL)
		exit(1);
	cmds[cmd_lines] = NULL;
	g_pipe_heredoc = malloc(sizeof(int *) * (cmd_lines + 1));
	if (g_pipe_heredoc == NULL)
		exit(1);
	while (i < cmd_lines + 1)
	{
		g_pipe_heredoc[i] = malloc(sizeof(int) * 2);
		if (g_pipe_heredoc[i] == NULL)
			exit(1);
		i++;
	}
	get_cmds(all_tokens, cmds, cmd_lines);
	return (cmds);
}

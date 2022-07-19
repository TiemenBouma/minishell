/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:52:01 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/19 21:42:49 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



// int	make_history(char *str)
// {
	
// }

int	get_cmd_line_count(char **tokens, int *cmd_count)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i][0] == '|')
			*cmd_count++;
		i++;
	}
	return (0);
}

int	get_cmd_len(char **tokens, int *current_token)
{
	int len;

	len = 0;
	while (tokens[*current_token] != '|')
	{
		len++;
		*current_token++;
	}
	return (len);
}

int	make_cmd(char **cmd_line, char **tokens, int current_token, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		cmd_line[i] = malloc(sizeof(char) * (ft_strlen(tokens[current_token + i]) + 1));
		i ++;
	}
	//COPY str
}

get_cmds(char **tokens, char ***cmds, int cmd_lines)
{
	int	current_token;
	int len;
	int	i;

	i = 0;
	current_token = 0;
	while (i < cmd_lines)
	{
		len = get_cmd_len(tokens, &current_token);
		cmds[i] = malloc(sizeof(char *) * (len + 1); //need to malloc one more *
		make_cmd(cmds[i], tokens, current_token, len);
	}
}

make_cmd_and_redir(char **tokens)
{
	int cmd_lines;
	char	***cmds;

	cmd_lines = 1;
	get_cmd_line_count(tokens, &cmd_lines);	
	cmds = malloc(sizeof(char **) * (cmd_lines + 1));
	cmds[cmd_lines] = NULL;
	get_cmds(tokens, cmds, cmd_lines);
	
}

int	main(void)//(int argc, char **argv, char **envp)
{
	// HIST_ENTRY **the_history_list;
	struct s_data	d;
	char	*str;
	// char	**root_path;
	//char	*cmd_path;
	int		i, j;
	//char	***cmd_arr;
	char	**tokens;
	char	***cmds;
	
	i = 0;
	j = 0;
	// (void) argc;
	// (void) argv;
	// root_path = find_path(envp);
	str = readline("SuperShell: ");
	//add_history(str);
	// while (root_path[i])
	// {
	// 	printf("%s\n", root_path[i]);
	// 	i++;
	// }
	i = 0;
	printf("readline:%s\n", str);
	tokens = ft_split_tokens(str, ' ');
	
	while (tokens[i])
	{
		printf("|%s|\n", tokens[i]);
		i++;
	}
	
	cmds = make_cmd_and_redir(tokens);
	//cmd_arr = parse_line(str);
	// while (cmd_arr[i])
	// {
	// 	j = 0;
	// 	while (cmd_arr[i][j])
	// 	{
	// 		printf("%s\n", cmd_arr[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	free_stuff(str);

	
}

// gcc main.c -lreadline

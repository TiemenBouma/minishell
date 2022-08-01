/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:42:24 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/01 15:07:04 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_tripple_str(char ***str, char *name)
{
	int		c1, c2;
	c1 = 0;
	printf("%s \t\t", name);
	while (str[c1])
	{
		c2 = 0;
		while (str[c1][c2])
		{
			printf("%s ", str[c1][c2]);
			c2++;
		}
		printf("\n");
		c1++;
	}
	printf("\n\n");
	return (0);
}

int	print_dubble_str(char **str, char *name)
{
	int		c1;
	c1 = 0;
	printf("%s \t\t", name);
	while (str[c1])
	{
		printf("|%s| ", str[c1]);
		c1++;
	}
	printf("\n");
	return (0);
}

int	print_cmd_info(struct s_cmd_lines *s)
{
	int i = 0;
	while (i < s->cmd_count)
	{
		printf("---------------------------------------\n");
		printf("CMDline_n %d\n", i);
		printf("has_in: %d has_out: %d\n", s->cmd_info[i].has_infile, s->cmd_info[i].has_outfile);
		printf("fd_in = %d fd_out = %d\n", s->cmd_info[i].pipe_cmd.fd_in, s->cmd_info[i].pipe_cmd.fd_out);
		if ( s->cmd_info[i].has_infile == 1)
			printf("infile:\t\t\t%s\n", s->cmd_info[i].infile);
		if ( s->cmd_info[i].has_outfile == 1)
			printf("outfile:\t\t%s\n", s->cmd_info[i].outfile);
		print_dubble_str(s->cmd_info[i].tokens, "CMDline_input:");
		print_dubble_str(s->cmd_info[i].pipe_cmd.exec_line, "Exec_line:");
		printf("\n");
		i++;
	}
	return (0);
}

int	print_structs(struct s_cmd_lines *s)
{
	// printf("\n\nInput _string:\n%s\n\n", s->input_str);
	// print_dubble_str(s->root_paths, "Root paths are: " );
	print_dubble_str(s->all_tokens, "all tokens are: ");
	// print_tripple_str(s->cmd_lines, "THe CMD_lines:");
	print_cmd_info(s);
	return (0);
}

int	print_linked_list(t_node **list)
{
	t_node	*current;

	current = *list;
	if (!current)
		return -1;
	while (current)
	{
		printf("%s\n", current->str);
		current = current->n;
	}
	return 0;
}
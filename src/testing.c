/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:42:24 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/08 14:58:15 by tbouma           ###   ########.fr       */
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

int	print_cmd_info(struct s_main *main_struct)
{
	int i = 0;
	while (i < main_struct->cmd_count)
	{
		printf("---------------------------------------\n");
		printf("CMDline_n %d\n", i);
		printf("has_in: %d has_out: %d\n", main_struct->curr_cmd_info[i].has_infile, main_struct->curr_cmd_info[i].has_outfile);
		printf("fd_in = %d fd_out = %d\n", main_struct->curr_cmd_info[i].exec.fd_in, main_struct->curr_cmd_info[i].exec.fd_out);
		if ( main_struct->curr_cmd_info[i].has_infile == 1)
			printf("infile:\t\t\t%s\n", main_struct->curr_cmd_info[i].infile);
		if ( main_struct->curr_cmd_info[i].has_outfile == 1)
			printf("outfile:\t\t%s\n", main_struct->curr_cmd_info[i].outfile);
		print_dubble_str(main_struct->curr_cmd_info[i].curr_line_tokens, "CMDline_input:");
		print_dubble_str(main_struct->curr_cmd_info[i].exec.exec_line, "Exec_line:");
		printf("\n");
		i++;
	}
	return (0);
}

int	print_structs(struct s_main *main_struct)
{
	// printf("\n\nInput _string:\n%s\n\n", main_struct->input_str);
	// print_dubble_str(main_struct->root_paths, "Root paths are: " );
	print_dubble_str(main_struct->all_tokens, "all tokens are: ");
	// print_tripple_str(main_struct->cmd_lines, "THe CMD_lines:");
	print_cmd_info(main_struct);
	return (0);
}

int	print_linked_list(t_node **list)
{
	t_node	*current;

	int i = 0;
	current = *list;
	if (!current)
		return -1;
	printf("\n");
	while (current)
	{
		printf("%d:\t%s\n", i, current->str);
		current = current->n;
		i++;
	}
	printf("\n");
	return 0;
}
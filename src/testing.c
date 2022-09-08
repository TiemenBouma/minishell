/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:42:24 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/08 11:51:32 by tbouma           ###   ########.fr       */
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
	if (str == NULL)
		return (0);
	printf("%s \t\t", name);
	while (str[c1])
	{
		printf("|%s|", str[c1]);
		
		c1++;
	}
	printf("\n");
	return (0);
}

int	print_cmd_info(struct s_main *m_s)
{
	int i = 0;
	while (i < m_s->cmd_count)
	{
		printf("---------------------------------------\n");
		printf("CMDline_n %d\n", i);
		printf("has_in: %d has_out: %d has_appendfile: %d has_heredoc: %d\n", m_s->c_s_arr[i].has_infile, m_s->c_s_arr[i].has_outfile, m_s->c_s_arr[i].has_appendfile, m_s->c_s_arr[i].has_heredoc);
		printf("fd_in = %d fd_out = %d\n", m_s->c_s_arr[i].exec.fd_in, m_s->c_s_arr[i].exec.fd_out);
		if ( m_s->c_s_arr[i].has_infile == 1)
			printf("infile:\t\t\t%s\n", m_s->c_s_arr[i].infile);
		if ( m_s->c_s_arr[i].has_outfile == 1)
			printf("outfile:\t\t%s\n", m_s->c_s_arr[i].outfile);
		if ( m_s->c_s_arr[i].has_appendfile == 1)
			printf("appendfile:\t\t%s\n", m_s->c_s_arr[i].appendfile);
		if ( m_s->c_s_arr[i].has_heredoc == 1)
			printf("heredoc:\t\t%s\n", m_s->c_s_arr[i].exec.heredoc);
		print_dubble_str(m_s->c_s_arr[i].curr_line_tokens, "CMDline_input:");
		print_dubble_str(m_s->c_s_arr[i].exec.exec_line, "Exec_line:");
		printf("\n");
		i++;
	}
	return (0);
}

int	print_structs(struct s_main *m_s)
{
	// printf("\n\nInput _string:\n%s\n\n", m_s->input_str);
	// print_dubble_str(m_s->root_paths, "Root paths are: " );
	if (m_s->all_tokens != NULL)
		print_dubble_str(m_s->all_tokens, "all tokens are: ");
	// print_tripple_str(m_s->cmd_lines, "THe CMD_lines:");
	print_cmd_info(m_s);
	return (0);
}

int	print_linked_list(t_node **list)
{
	t_node	*current;

	int i = 0;
	current = *list;
	if (!current)
		return -1;
	dprintf(STDERR_FILENO, "\n");
	while (current)
	{
		dprintf(STDERR_FILENO, "%d:\t%s\n", i, current->str);
		current = current->n;
		i++;
	}
	printf("\n");
	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_shell_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:34:40 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/24 10:35:23 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"
#include "stdlib.h"

int	main(void)
{
	int				i;
	static t_part	parts1s[] = {{"bla asf", NORMAL},
	{"een twee drie vier vijf", NORMAL},
	{"blie bloe", NORMAL},
	{NULL, NORMAL}};
	t_part			*parts1;

	parts1 = ft_memdup(parts1s, sizeof(parts1s));
	i = 0;
	while (parts1[i].part)
	{
		parts1[i].part = ft_strdup(parts1[i].part);
		i++;
	}
	replace_parts(&parts1, 1);
	print_parts(parts1);
	replace_parts(&parts1, 6);
	print_parts(parts1);
	ft_free_parts(parts1);
}

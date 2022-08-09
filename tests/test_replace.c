/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_shell_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:34:40 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/23 13:44:55 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"
#include "stdlib.h"

void	replace_print(char **s2, int start, int len, char *rep)
{
	ft_replace(s2, start, len, rep);
	printf("out: %s\n", *s2);
}

int	main(void)
{
	char	*s1;
	char	*s2;

	s1 = "hallo";
	s2 = ft_strdup(s1);
	replace_print(&s2, 0, 1, "g");
	replace_print(&s2, 1, 2, "xy");
	replace_print(&s2, 3, 1, "zw");
	replace_print(&s2, 4, 0, "");
	free(s2);
}

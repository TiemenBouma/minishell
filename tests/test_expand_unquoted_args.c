/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_shell_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:34:40 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/29 09:12:35 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"
#include "stdlib.h"

int	main(void)
{
	char				*string;
	static const char	*envstrs[] = {"BLA=hoi", NULL};
	static t_env		s_env = {(char **)envstrs, 1, 1};
	t_part				*parts;

	string = "*$BLA";
	parts = quote_split(string);
	print_parts(parts);
	expand_unquoted_args(parts, 0, &s_env);
	print_parts(parts);
	ft_free_parts(parts);
	string = "$BLA*";
	parts = quote_split(string);
	print_parts(parts);
	expand_unquoted_args(parts, 0, &s_env);
	print_parts(parts);
	ft_free_parts(parts);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wildcard.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:35:14 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/23 13:43:52 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"

int	main(void)
{
	char		*result;
	static int	quoted1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	static int	quoted2[] = {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	result = ft_wildcard(ft_strdup("test_wi*c"), quoted1);
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("test_wi*.c"), quoted1);
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("*wildcard.c"), quoted1);
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("*wild*a*r*.c"), quoted1);
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("*wild**.c"), quoted1);
	printf("%s\n\n", result);
	free(result);
	result = ft_wildcard(ft_strdup("*wild**.c"), quoted2);
	printf("%s\n\n", result);
	free(result);
}

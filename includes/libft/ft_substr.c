/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 11:29:04 by tbouma        #+#    #+#                 */
/*   Updated: 2022/09/13 11:14:04 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	src_size;

	if (s == NULL)
		return (NULL);
	src_size = ft_strlen(s);
	if (start > src_size)
	{
		ptr = ft_calloc(1, sizeof(char));
		return (ptr);
	}
	if (src_size - start < len)
		len = src_size - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	src_size = 0;
	while (s[start + src_size] && len > src_size)
	{
		ptr[src_size] = s[start + src_size];
		src_size++;
	}
	ptr[src_size] = '\0';
	return (ptr);
}

// #include <stdio.h>

// int main(void)
// {
// 	char *ptr = "TiemenDAN";
// 	char *cpy;
// 	char *cpy2;

// 	cpy = ft_substr(ptr, 0, 10);
// 	printf("sub = |%s|\n", cpy);
// 	cpy2 = ft_substr(ptr, 10, 3);
// 	printf("sub = |%s|\n", cpy2);
// 	cpy = ft_substr(ptr, 1, 1);
// 	printf("sub = |%s|\n", cpy);
// 	cpy2 = ft_substr(ptr, 0, 0);
// 	printf("sub = |%s|\n", cpy2);
// 	cpy2 = ft_substr(ptr, 8, 8);
// 	printf("sub = |%s|\n", cpy2);
// }
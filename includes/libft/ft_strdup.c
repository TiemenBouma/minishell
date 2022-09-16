/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 11:27:57 by tbouma        #+#    #+#                 */
/*   Updated: 2022/09/16 09:20:46 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		len_s1;

	len_s1 = ft_strlen(s1);
	ptr = malloc((len_s1 + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[len_s1] = '\0';
	while (len_s1 > 0)
	{
		len_s1--;
		ptr[len_s1] = s1[len_s1];
	}
	return (ptr);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char	*string1 = "coucou\0";
// 	char	*cpy;
// 	char	*cpy2;

// 	cpy = ft_strdup(string1);
// 	printf("%s$\n", cpy);
// 	printf("string len: %lu\n", strlen(cpy));
// 	cpy2 = strdup(string1);
// 	printf("%s$\n", cpy2);
// 	printf("string len: %lu\n", strlen(cpy2));
// 	free(cpy);
// 	free(cpy2);
// 	return (0);
// }

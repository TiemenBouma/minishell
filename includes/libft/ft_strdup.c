/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:27:57 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:28:12 by tbouma           ###   ########.fr       */
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
	while (len_s1 >= 0)
	{
		len_s1--;
		ptr[len_s1] = s1[len_s1];
	}
	return (ptr);
}

// int main(void)
// {
// 	char	string1[] = "coucou";
// 	char	*cpy;
// 	char	*cpy2;
//
// 	cpy = ft_strdup(string1);
// 	printf("%s$\n", cpy);
// 	printf("string len: %lu\n", strlen(cpy));
// 	cpy2 = ft_strdup(string1);
// 	printf("%s$\n", cpy2);
// 	printf("string len: %lu\n", strlen(cpy2));
// }

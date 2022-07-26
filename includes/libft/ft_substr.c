/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:29:04 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/26 15:41:56 by tbouma           ###   ########.fr       */
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
	if (src_size - start < len && src_size >= start)
		len = src_size - start;
	if (start > src_size)
	{
		ptr = ft_calloc(1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	ptr = (char *) malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	src_size = 0;
	while (s[start] && len > src_size)
	{
		ptr[src_size] = s[start + src_size];
		src_size++;
	}
	ptr[src_size] = '\0';
	return (ptr);
}

// int main(void)
// {
// 	char *ptr = "Tiemen";
// 	char *cpy;
// 	char *cpy2;

// 	cpy = ft_substr(ptr, 2, 3);
// 	printf("sub = %s\n", cpy);
// 	cpy2 = ft_substr(ptr, 2, 3);
// 	printf("sub = %s\n", cpy2);
// }
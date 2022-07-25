/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:29:04 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/25 16:40:59 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	len_str;

	if (s == NULL)
		return (NULL);
	len_str = ft_strlen(s);
	if (len_str - start < len && (len_str < start))
		len = len_str - start;
	if (start > len_str)
	{
		ptr = ft_calloc(1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	len_str = 0;
	while (s[start] && len > len_str)
	{
		ptr[len_str] = s[start + len_str];
		len_str++;
	}
	ptr[len_str] = '\0';
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
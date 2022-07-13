/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:29:04 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:29:51 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (i - start < len && !(i < start))
		len = i - start;
	if (start > i)
	{
		ptr = ft_calloc(1, sizeof(char));
		return (ptr);
	}
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[start] && len > i)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
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
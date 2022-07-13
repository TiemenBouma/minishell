/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:28:47 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:30:53 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*find_needle(const char *haystack, const char *needle,
				size_t len_needle, size_t len)
{
	size_t	index_haystack;
	size_t	index_needle;

	index_haystack = 0;
	while ((haystack[index_haystack] && index_haystack <= (len - len_needle)))
	{
		index_needle = 0;
		while (needle[index_needle])
		{
			if (haystack[index_haystack + index_needle] == needle[index_needle])
			{
				index_needle++;
				if (needle[index_needle] == '\0')
					return (&((char *)haystack)[index_haystack]);
			}
			if (haystack[index_haystack + index_needle] != needle[index_needle])
				break ;
		}
		index_haystack++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	char	*ptr;

	len_needle = ft_strlen(needle);
	if (needle[0] == 0)
		return (&((char *)haystack)[0]);
	if (len == 0)
		return (0);
	if (len_needle > len)
		len_needle = len;
	ptr = find_needle(haystack, needle, len_needle, len);
	return (ptr);
}

// int main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "abcd";;
// 	char *check;

// 	check = ft_strnstr(haystack, needle, 9);
// 	printf("Haystack = %s\n", haystack);
// 	printf("Needle = %s\n", needle);
// 	printf("Find = %s\n\n", check);

// 	check = strnstr(haystack, needle, 9);
// 	printf("Haystack = %s\n", haystack);
// 	printf("Needle = %s\n", needle);
// 	printf("Find = %s\n\n", check);
// }

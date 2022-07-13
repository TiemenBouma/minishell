/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:28:24 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:29:51 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	copy_string(char *dest, char *src, size_t max_len, size_t len_dest)
{
	int	i;

	i = 0;
	while (max_len > len_dest + 1 && src[i])
	{
		((char *)dest)[len_dest] = ((char *)src)[i];
		i++;
		len_dest++;
	}
	dest[len_dest] = '\0';
}

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen((char *)src);
	if (dest_size == 0)
		return (len_src);
	if (dest_size < len_dest)
		return (len_src + dest_size);
	copy_string(dest, (char *)src, dest_size, len_dest);
	return (len_dest + len_src);
}

// int	main(void)
// {	
// 	char src[20] = "Apple";
// 	char dest[20] = "Cow";
// 	char srcCp[20] = "Apple";
// 	char destCp[20] = "Cow";
// 	int i;
// 	int j;
// 	int max_len = 5;

// 	printf("Dest = %s\n", dest);
// 	printf("Src  = %s\n", src);
// 	printf("max_len  = %d\n\n", max_len);
// 	i = ft_strlcat(dest, src, max_len);
// 	printf("Dest = %s\n", dest);
// 	printf("Src  = %s\n", src);
// 	printf("size to copy  = %d\n\n", i);
// 	j = strlcat(destCp, srcCp, max_len);
// 	printf("Or Dest = %s\n", destCp);
// 	printf("Or Src  = %s\n", srcCp);
// 	printf("Or Size to copy  = %d\n\n", j);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:28:28 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:29:51 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	len_src;
	size_t	i;

	i = 0;
	len_src = ft_strlen(src);
	if (dest_size == 0)
		return (len_src);
	while (dest_size > 1 + i && src[i])
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	dest[i] = '\0';
	return (len_src);
}

// int	main(void)
// {
// 	char src[] = "appels";
// 	char dest[] = "Koeien";
// 	int i;

// 	i = ft_strlcpy(dest, src, 15);
// 	printf("Dest = %s\n", dest);
// 	printf("Src  = %s\n", src);
// 	printf("Src_size  = %d\n", i);
// }

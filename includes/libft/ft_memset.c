/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:27:23 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:28:12 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *str, int c, unsigned int len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	char	zin[] = "test mijn appels";

// 	ft_memset(zin, 'b', 3);
// 	printf("%s\n", zin);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:28:52 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:29:51 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)s;
	i = ft_strlen(s);
	if ((char)c == '\0')
		return (ptr + i);
	i--;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (ptr + i);
		i--;
	}
	return (0);
}

// int	main(void)
// {
// 	char			str[10] = "Tiemen";
// 	unsigned char	c = '\0';
// 	char			*pnt;
//
// 	pnt = ft_strrchr(str, c);
// 	printf("%c\n", *pnt);
// }

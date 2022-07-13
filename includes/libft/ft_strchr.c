/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:27:52 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:28:12 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	char	character;

	i = 0;
	character = (char)c;
	ptr = (char *)s;
	if (character == '\0')
		return (ptr + ft_strlen(s));
	while (ptr[i])
	{
		if (ptr[i] == character)
			return (ptr + i);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char			str[10] = "Tiemen";
// 	unsigned char	c = '\0';
// 	char			*pnt;

// 	pnt = ft_strrchr(str, c);
// 	printf("%s\n", pnt);
// }

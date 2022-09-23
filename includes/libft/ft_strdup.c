/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:27:57 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/23 10:07:17 by tbouma           ###   ########.fr       */
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
		exit (1);
	ptr[len_s1] = '\0';
	while (len_s1 > 0)
	{
		len_s1--;
		ptr[len_s1] = s1[len_s1];
	}
	return (ptr);
}

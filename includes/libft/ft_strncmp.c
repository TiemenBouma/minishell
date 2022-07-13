/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:28:41 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:29:51 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	i = 0;
	while (n > i && ptr1[i] && ptr2[i])
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	if (n == i)
		return (0);
	return (ptr1[i] - ptr2[i]);
}

// int main(void)
// {
// 	char string1 [20] = "Tiemes";
// 	char string2 [20] = "Tie";
// 	int check;

// 	check = ft_strncmp(string1, string2, 4);
// 	printf("%d\n", check);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ull_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:29:24 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/16 13:55:54 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*base_mod(unsigned long long ull, int base, int count, char *ptr)
{
	long long	remainder;

	while (ull > 0)
	{
		remainder = (ull % base);
		if (remainder < 10)
			ptr[count - 1] = remainder + '0';
		else
			ptr[count - 1] = remainder + 55;
		count--;
		ull /= base;
	}
	return (ptr);
}

char	*ft_ull_base(unsigned long long ull, int base)
{
	char				*ptr;
	unsigned long long	copy_ull;
	int					count;

	count = 0;
	if (ull == 0)
		return (ft_strdup("0"));
	copy_ull = ull;
	while (copy_ull != 0)
	{
		copy_ull /= base;
		count++;
	}
	ptr = malloc((count + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[count] = '\0';
	ptr = base_mod(ull, base, count, ptr);
	return (ptr);
}

//int main(void)
//{
//	char *ptr;
//
//	ptr = ft_ull_base(12345, 16);
//	printf("in main fucntie!:%s", ptr);
//}
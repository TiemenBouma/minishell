/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:26:25 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:28:12 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_string_from_int(int n, int is_min, int len_num, char *ptr)
{
	len_num--;
	if (n == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	while ((len_num > 0 && is_min == 1) || (len_num >= 0 && is_min == 0))
	{
		ptr[len_num] = (n % 10) + '0';
		len_num--;
		n /= 10;
	}
	return (ptr);
}

char	*len_int_malloc(int len_n, int is_min)
{
	char	*ptr;

	ptr = (char *) malloc((len_n + 1) * sizeof(char));
	if (ptr == 0)
		return (NULL);
	if (is_min == 1)
		ptr[0] = '-';
	ptr[len_n] = '\0';
	return (ptr);
}

int	len_int(int n, int is_min)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	i = i + is_min;
	return (i);
}

char	*ft_itoa(int n)
{
	int		is_min;
	int		len_num;
	char	*ptr;

	is_min = 0;
	if (n == -2147483648)
	{
		ptr = ft_strdup("-2147483648");
		return (ptr);
	}
	if (n < 0)
	{
		n *= -1;
		is_min++;
	}
	len_num = len_int(n, is_min);
	ptr = len_int_malloc(len_num, is_min);
	if (ptr == NULL)
		return (NULL);
	make_string_from_int(n, is_min, len_num, ptr);
	return (ptr);
}

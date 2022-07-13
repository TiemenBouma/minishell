/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:28:33 by tbouma            #+#    #+#             */
/*   Updated: 2022/02/07 14:23:32 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	recursion(long long n, int base, int fd)
{
	char	d;
	int		count;

	count = 0;
	while (n > 0)
	{
		d = (n % base);
		if (d < 10)
			d = d + '0';
		else
			d = d + 'a' - 10;
		n /= base;
		count += recursion(n, base, fd);
		count += write(fd, &d, sizeof(char));
		n = 0;
	}
	return (count);
}

int	ft_putnbr_base_fd(long long n, int base, int fd)
{
	int	count;

	count = 0;
	if (n == 0)
		return (write(fd, "0", 1));
	else if (n > 0)
		return (recursion(n, base, fd));
	else if (n < 0)
	{
		count = write(fd, "-", 1);
		n *= -1;
		count += recursion(n, base, fd);
	}
	return (count);
}

// int main(void)
// {
// 	ft_putnbr_base_fd(-2147483648, 16, 1);
// }

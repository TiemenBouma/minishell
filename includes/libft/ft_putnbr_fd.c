/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:27:38 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:28:12 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	recursion(long long n, int fd)
{
	char	d;
	int		count;

	count = 0;
	while (n > 0)
	{
		d = (n % 10) + '0';
		n /= 10;
		count += recursion(n, fd);
		count += write(fd, &d, sizeof(char));
		n = 0;
	}
	return (count);
}

int	ft_putnbr_fd(long long n, int fd)
{
	int	count;

	count = 0;
	if (n == 0)
		return (write(fd, "0", 1));
	else if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	else if (n > 0)
		return (recursion(n, fd));
	else if (n < 0)
	{
		count = write(fd, "-", 1);
		n *= -1;
		count += recursion(n, fd);
	}
	return (count);
}

// int main(void)
// {
// 	ft_putnbr_fd(87, 1);
// }

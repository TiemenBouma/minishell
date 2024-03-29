/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:25:40 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/23 09:55:49 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		exit (1);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// int main(void)
// {
// char *ptr;

// ptr = ft_calloc(5, sizeof(char));
// printf("%s\n", ptr);
// }

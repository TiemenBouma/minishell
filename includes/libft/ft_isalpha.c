/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:25:59 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:28:12 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// int	main(void)
// {
// 	int	var1;
// 	int	var2;
// 	int	var3;
// 	int	var4;

// 	var1 = ft_isalpha('a');
// 	var2 = ft_isalpha('z');
// 	var3 = ft_isalpha('b');
// 	var4 = ft_isalpha('1');
// 	printf("%d\n%d\n%d\n%d\n", var1, var2, var3, var4);
// }

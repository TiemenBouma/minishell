/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:00:43 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/31 11:21:36 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **s)
{
	int	i = 1;
	int	nl;

	i = 1;
	nl = 1; 
	if (s[1] && check_n_flag(s[1]))
	{
		nl = 0;
		i = 2;
	}
	while (s[i] && check_n_flag(s[i]))
		i++;
	while (s[i])
	{
		ft_putstr_fd(s[i], 1);
		if (nl == 1)
			write(1, " ", 2);
		i++;
	}
	if (nl == 1)
		ft_putstr_fd("\n", 1);

}

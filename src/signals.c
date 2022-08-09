/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:32:41 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/09 09:56:24 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sigint_handler_in_process(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	//printf("\n");
}

void	sigquit_handler_in_process(int sig)
{
	(void) sig;
	printf("Quit: %d\n", sig);
}

void	sigint_handler_nonl(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sigint_handler(int sig)
{
	write(1, "\n", 1);
	//printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	signals_handeler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

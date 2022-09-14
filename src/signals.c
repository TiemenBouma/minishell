/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:32:41 by tbouma            #+#    #+#             */
/*   Updated: 2022/09/14 13:16:56 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler_in_process(int sig)
{
	(void) sig;
}

void	sigquit_handler_in_process(int sig)
{
	(void) sig;
	printf("Quit: %d\n", sig);
}

void	ft_suppress_output(void)
{
	struct termios	new_settings;

	if (tcgetattr(0, &new_settings))
		perror("minishell: tcsetattr");
	new_settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &new_settings))
		perror("minishell: tcsetattr");
}

void	sigint_handler(int sig)
{
	ft_suppress_output();
	write(1, "\n", 1);
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

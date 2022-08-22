/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:32:41 by tbouma            #+#    #+#             */
/*   Updated: 2022/08/22 12:18:38 by tbouma           ###   ########.fr       */
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

void    ft_suppress_output(void)
{
    struct termios    new_settings;

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

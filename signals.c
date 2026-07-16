/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 22:24:06 by walneama          #+#    #+#             */
/*   Updated: 2026/07/16 18:50:43 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_interactive(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
}

void	sig_child(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_IGN);
}

int	check_sigint(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

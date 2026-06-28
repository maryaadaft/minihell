/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2026/06/27 00:00:00 by walneama          #+#    #+#             */
/*   Updated: 2026/06/27 00:00:00 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint = 0;

/* Interactive SIGINT: don't kill the shell, just flag it so the caller
   can print a fresh prompt. We do NOT use SA_RESTART so readline's read()
   returns EINTR promptly. */
static void	sigint_handler(int sig)
{
	(void)sig;
	g_sigint = 1;
	write(STDOUT_FILENO, "\n", 1);
}

/* Install interactive handlers: SIGINT -> flag + newline, SIGQUIT ignored. */
void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0; // no SA_RESTART: interrupt blocking reads
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/* Clear the interrupt flag (call at the start of each prompt iteration). */
void	reset_sigint(void)
{
	g_sigint = 0;
}

/* Children must restore default disposition so real commands (cat, grep, ...)
   actually die on Ctrl+C instead of running our shell's handler. */
void	reset_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

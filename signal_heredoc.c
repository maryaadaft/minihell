/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:50:15 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/16 18:51:04 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_heredoc(int signal)
{
	(void)signal;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_done = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

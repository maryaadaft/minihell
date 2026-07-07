/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 22:24:06 by walneama          #+#    #+#             */
/*   Updated: 2026/07/07 17:57:51 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 
Context              SIGINT (Ctrl+C)        SIGQUIT (Ctrl+\)
─────────────────    ──────────────────     ────────────────
prompt (idle)        new prompt + newline   ignore
running command      interrupt child        ignore
heredoc input        cancel heredoc         ignore

*/

// SIGINT (Ctrl + C)
void handle_sigint(int signal)
{
	(void)signal;

	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();			// move the cursor to the new line
	rl_replace_line("", 0);		// clears the buffer
	rl_redisplay();				// redisplay our "minishell$"
}

void sig_interactive()
{
	signal(SIGINT, handle_sigint); // if (Ctrl + C) -> call handle_sigint to handle it
	signal(SIGQUIT, SIG_IGN); // if (Ctrl+\) -> just ignore
}

void handle_sigint_child(int sig)
{
    (void)sig;
    g_signal = SIGINT;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
}

// default handeling
void sig_child()
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_IGN);
}

void handle_sigint_heredoc(int signal)
{
	(void)signal;
    g_signal = SIGINT;
    write(1, "\n", 1);
    rl_done = 1;
    rl_on_new_line();
    rl_replace_line("", 0);
}

void sig_heredoc()
{
	 struct sigaction sa;

    sa.sa_handler = handle_sigint_heredoc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;  // NO SA_RESTART → syscalls won't restart after signal
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
int	check_sigint(void)
{
    if (g_signal == SIGINT)
        rl_done = 1;
    return (0);
}
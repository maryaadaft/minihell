/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 18:14:09 by walneama          #+#    #+#             */
/*   Updated: 2026/07/23 20:10:53 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_pipes(int *prev_pipe, int *current_pipe, t_cmd *cmds)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (cmds->next)
	{
		prev_pipe[0] = current_pipe[0];
		prev_pipe[1] = current_pipe[1];
	}
}

static pid_t	run_pipe(t_cmd *cmds, t_shell *shell)
{
	int		prev_pipe[2];
	int		current_pipe[2];
	pid_t	pid;
	pid_t	last_pid;

	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	while (cmds)
	{
		if (cmds->next)
			pipe(current_pipe);
		pid = fork();
		if (pid == 0)
			pipe_child(cmds, prev_pipe, current_pipe, shell);
		manage_pipes(prev_pipe, current_pipe, cmds);
		if (!cmds->next)
			last_pid = pid;
		cmds = cmds->next;
	}
	return (last_pid);
}

static void	wait_for_all(pid_t last_pid, t_shell *shell)
{
	pid_t	reaped;
	int		status;

	reaped = waitpid(-1, &status, 0);
	while (reaped > 0)
	{
		if (reaped == last_pid)
		{
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		reaped = waitpid(-1, &status, 0);
	}
}

void	ft_pipe(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*temp;
	pid_t	last_pid;

	temp = cmds;
	while (temp)
	{
		if (prep_heredocs(temp, shell) == -1)
		{
			shell->exit_status = 130;
			return ;
		}
		temp = temp->next;
	}
	sig_child();
	last_pid = run_pipe(cmds, shell);
	wait_for_all(last_pid, shell);
}

void	pipe_child(t_cmd *cmd, int *prev_pipe, int *curr_pipe, t_shell *shell)
{
	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (cmd->next)
	{
		dup2(curr_pipe[1], STDOUT_FILENO);
		close(curr_pipe[0]);
		close(curr_pipe[1]);
	}
	if (apply_redirs(cmd->redirs) == -1)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(shell->exit_status);
	if (is_builtin(cmd->args[0]))
	{
		run_builtin(cmd, shell);
		exit(shell->exit_status);
	}
	execute_child(cmd, shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 18:14:09 by walneama          #+#    #+#             */
/*   Updated: 2026/06/23 17:53:04 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pipe(t_cmd *cmds, t_shell *shell)
{
	int prev_pipe[2] = {-1, -1};
	int current_pipe[2];
	pid_t pid;
	pid_t last_pid;
	pid_t reaped; // interesting!!
	int status;

	while(cmds)
	{
		if (cmds->next)
			pipe(current_pipe);
		pid = fork();
		if (pid == 0)
			pipe_child(cmds, prev_pipe, current_pipe, shell);
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
		if (!cmds->next)
			last_pid = pid;
		cmds = cmds->next;
	}
	while ((reaped = waitpid(-1, &status, 0)) > 0)
	{
		if (reaped == last_pid)
			shell->exit_status = WEXITSTATUS(status);
	}
}

void pipe_child(t_cmd *cmd, int *prev_pipe, int *curr_pipe, t_shell *shell)
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
	if (is_builtin(cmd->args[0]))
	{
		run_builtin(cmd, shell);
		exit(shell->exit_status);
	}
	execute_child(cmd, shell);
}

void	execute_child(t_cmd *cmd, t_shell *shell)
{
	// execute_child? 💀💀💀💀 what a name!
	char	*valid_path;
	char	**envp;

	if (cmd->args[0][0] == '/')
    	valid_path = ft_strdup(cmd->args[0]);
	else
		valid_path = get_path(cmd, shell);
	if (!valid_path)
	{
		write(2, "minishell: command not found\n", 29);
		exit(127);
	}
	envp = env_to_array(shell);
	execve(valid_path, cmd->args, envp);
	perror("execve");
	free(valid_path);
	free_args(envp);
	exit(126);
}

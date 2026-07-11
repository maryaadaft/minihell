/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:53:11 by walneama          #+#    #+#             */
/*   Updated: 2026/07/11 19:42:43 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void child_process(t_cmd *cmd, char *valid_path, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	if (apply_redirs(cmd->redirs) == -1)
		exit(1);
	execve(valid_path, cmd->args, envp);
	perror("execve");
	free(valid_path);
	free_args(envp);
	exit(127);
}
static void	wait_child(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}
static int setup_execute(t_cmd *cmd, t_shell *shell, char **path, char ***envp)
{
	if (cmd->args[0][0] == '/')
		*path = ft_strdup(cmd->args[0]);
	else
		*path = get_path(cmd, shell);
	if (!*path)
	{
		write(2, "minishell: command not found\n", 29);
		shell->exit_status = 127;
		return (0);
	}
	*envp = env_to_array(shell);
	if (!*envp)
	{
		free(*path);
		malloc_exit(shell);
	}
	return (1);
}

void	ft_execute(t_cmd *cmd, t_shell *shell)
{
	char *valid_path;
	char **envp;
	pid_t	pid;

	if (prep_heredocs(cmd, shell) == -1)
	{
		shell->exit_status = 130;	
		return ;
	}
	if (!cmd->args || !cmd->args[0]) //for empty command with redir
    {
        apply_redir_only(cmd->redirs, shell);
        return ;
    }
	if (!setup_execute(cmd, shell, &valid_path, &envp))
		return ;
	sig_child(); 
	pid = fork();
	if (pid == 0)
		child_process(cmd, valid_path, envp);
	wait_child(pid, shell);
	free (valid_path);
	free_args(envp);
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

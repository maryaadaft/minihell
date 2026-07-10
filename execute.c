/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:53:11 by walneama          #+#    #+#             */
/*   Updated: 2026/07/10 18:20:52 by walneama         ###   ########.fr       */
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

char	*get_path(t_cmd *cmd, t_shell *shell)
{
	t_env	*path_node;
	char	**folder;
	char	*full_path;
	int		i;
	char	*temp;

	i = -1;
	path_node = find_env(shell, "PATH");
	if (!path_node)
		return (NULL);
	folder = ft_split(path_node->value, ':');
	while (folder[++i])
	{
		temp = ft_strjoin(folder[i], "/");
		full_path = ft_strjoin(temp, cmd->args[0]);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_args(folder);
			return (full_path);
		}
		free (full_path);
	}
	free_args(folder);
	return (NULL);
}

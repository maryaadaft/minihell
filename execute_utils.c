/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 19:36:29 by walneama          #+#    #+#             */
/*   Updated: 2026/07/11 20:26:06 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (1);
	return (0);
}

void	run_builtin(t_cmd *cmd, t_shell *shell)
{
	shell->exit_status = 0;
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ft_cd(cmd, &shell);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ft_pwd(cmd);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		shell->exit_status = ft_exit(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ft_env(shell);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		ft_unset(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		ft_export(cmd, shell);
}

void	run_builtin_with_redir(t_cmd *cmd, t_shell *shell)
{
	int	old_stdin;
	int	old_stdout;

	if (!cmd->redirs)
		return (run_builtin(cmd, shell));
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (prep_heredocs(cmd, shell) == -1)
		shell->exit_status = 130;
	else if (apply_redirs(cmd->redirs) == 0)
		run_builtin(cmd, shell);
	else
		shell->exit_status = 1;
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdin);
	close(old_stdout);
}

void	pipe_child(t_cmd *cmd, int *prev_pipe, int *curr_pipe, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
		exit(0);
	if (is_builtin(cmd->args[0]))
	{
		run_builtin(cmd, shell);
		exit(shell->exit_status);
	}
	execute_child(cmd, shell);
}

char	*get_path(t_cmd *cmd, t_shell *shell)
{
	t_env	*path_node;
	char	**folder;
	char	*full_path;
	int		i;
	char	*temp;

	i = -1;
	if (!cmd->args[0][0])
		return (NULL);
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

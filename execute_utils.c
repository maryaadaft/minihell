/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 19:36:29 by walneama          #+#    #+#             */
/*   Updated: 2026/07/18 17:00:57 by walneama         ###   ########.fr       */
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
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		ft_echo(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ft_cd(cmd, &shell);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ft_pwd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(shell, cmd);
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

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (prep_heredocs(cmd, shell) == -1)
		shell->exit_status = 130;
	else if (apply_redirs(cmd->redirs) == 0)
		run_builtin(cmd, shell);
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdin);
	close(old_stdout);
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

char	*resolve_cmd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK) == -1)
		{
			write(2, "minishell: ", 12);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": No such file or directory\n", 29);
			return (NULL);
		}
		path = ft_strdup(cmd->args[0]);
	}
	else
		path = get_path(cmd, shell);
	if (!path)
		write(2, "minishell: command not found\n", 29);
	return (path);
}

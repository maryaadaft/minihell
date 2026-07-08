/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:53:11 by walneama          #+#    #+#             */
/*   Updated: 2026/07/08 13:40:35 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_cmd *cmd, t_shell *shell)
{
	char *valid_path;
	char **envp;
	pid_t	pid;
	int		status;

	if (prep_heredocs(cmd, shell) == -1)
	{
		shell->exit_status = 130;	
		return ;
	}
	if (cmd->args[0][0] == '/')
    	valid_path = ft_strdup(cmd->args[0]);
	else
		valid_path = get_path(cmd, shell);
	if (!valid_path)
	{
		write(2, "minishell: command not found\n", 29);
		shell->exit_status = 127;
		return ;
	}
	envp = env_to_array(shell);
	sig_child(); 
	pid = fork();
	if (pid == 0)
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
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
    	write(2, "Quit (core dumped)\n", 19);
	free (valid_path);
	free_args(envp);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

char **env_to_array(t_shell *shell)
{
	int len;
	char **envp;
	char *temp_str;
	t_env *temp;
	int i;

	i = 0;
	temp = shell->env;
	len = env_len(shell);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	while (temp)
	{
		temp_str = ft_strjoin(temp->key, "=");
		if (!temp_str)
		{
			free_args(envp);
			return (NULL);
		}
		envp[i] = ft_strjoin(temp_str, temp->value);
		free(temp_str);
		if (!envp[i])
		{
			free(temp_str);
			free_args(envp);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

int env_len(t_shell *shell)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = shell->env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:53:11 by walneama          #+#    #+#             */
/*   Updated: 2026/06/10 21:06:19 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	pid = fork();
	if (pid == 0)
	{
		execvp(cmd->args[0], cmd->args);
		perror("execvp");
		exit(1);
	}
	waitpid(pid, &status, 0);
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
	len = ft_lstsize(shell->env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	while (temp)
	{
		temp_str = ft_strjoin(temp->key, "=");
		if (!temp_str)
			return (NULL);
		printf("before: %s\n", temp_str);
		envp[i] = ft_strjoin(temp_str, temp->value);
		printf("After : %s\n", envp[i]);
		free(temp_str);
		if (!envp[i])
			return (NULL);
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

char	*get_path(t_shell *shell, t_cmd *cmd)
{
	char *full_path;
	char **folder;
	int i;
	char *temp;

	i = 0;
	full_path = find_env(shell, "PATH");
	folder = ft_split(full_path, ':');
	while (folder[i])
	{
		temp = ft_strjoin(folder[i], "/");
		full_path = ft_strjoin(temp, cmd->args[0]);
		free(temp);
		
	}
}
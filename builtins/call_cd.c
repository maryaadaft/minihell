/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:55:50 by walneama          #+#    #+#             */
/*   Updated: 2026/07/17 22:03:43 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_path(t_cmd *cmd, t_shell *shell)
{
	t_env	*last_pwd;
	char	*home;

	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		last_pwd = find_env(shell, "OLDPWD");
		if (last_pwd)
			return (ft_strdup(last_pwd->value));
		return (NULL);
	}
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "~", 2) != 0)
		return (ft_strdup(cmd->args[1]));
	home = get_home(shell);
	if (!home)
		return (NULL);
	return (ft_strdup(home));
}

static int change_dir(char *path, t_shell *shell)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (chdir(path) == -1)
		return (1);
	update_pwds(shell, cwd, 0);
	getcwd(cwd, sizeof(cwd));
	update_pwds(shell, cwd, 1);
	return (0);
}

void	ft_cd(t_cmd *cmd, t_shell **shell)
{
	char	*path;

	path = NULL;
	if (cmd->args[2])
		write(2, "minishell: cd: too many arguments\n", 34);
	path = cd_path(cmd, *shell);
	if (!path)
	{
		if (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0)
			num_err_msg("minishell: cd: OLDPWD not set");
		else
			num_err_msg("minishell: cd: HOME not set");
		(*shell)->exit_status = 1;
		return ;
	}
	if (change_dir(path, *shell))
	{
		if (!cmd->args[2])
			fd_error(cmd->args[1], *shell, "cd: ");
		(*shell)->exit_status = 1;
		free(path);
		return ;
	}
	free(path);
	(*shell)->exit_status = 0;
}

char	*get_home(t_shell *shell)
{
	t_env	*head_env;
	char	*path;

	head_env = shell->env;
	path = NULL;
	while (head_env)
	{
		if (ft_strncmp(head_env->key, "HOME", 5) == 0)
		{
			path = head_env->value;
		}
		head_env = head_env->next;
	}
	return (path);
}

void	update_pwds(t_shell *shell, char *cwd, int flag_path)
{
	t_env	*head_env;

	head_env = shell->env;
	while (head_env)
	{
		if (flag_path == 0 && ft_strncmp(head_env->key, "OLDPWD", 7) == 0)
		{
			free(head_env->value);
			head_env->value = ft_strdup(cwd);
		}
		else if (flag_path == 1 && ft_strncmp(head_env->key, "PWD", 4) == 0)
		{
			free(head_env->value);
			head_env->value = ft_strdup(cwd);
		}
		head_env = head_env->next;
	}
}

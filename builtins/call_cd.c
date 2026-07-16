/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:55:50 by walneama          #+#    #+#             */
/*   Updated: 2026/07/16 18:55:06 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_cmd *cmd, t_shell **shell)
{
	char	cwd[PATH_MAX];
	char	*path;
	t_env	*last_pwd;

	path = NULL;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		last_pwd = find_env(*shell, "OLDPWD");
		if (last_pwd)
			path = ft_strdup(last_pwd->value);
	}
	else if (cmd->args[1] && ft_strncmp(cmd->args[1], "~", 2) != 0)
		path = ft_strdup(cmd->args[1]);
	else
		path = ft_strdup(get_home(*shell));
	if (!path)
		return ((void)num_err_msg("minishell: cd: OLDPWD not set"));
	getcwd(cwd, sizeof(cwd));
	update_pwds(*shell, cwd, 0);
	if (chdir(path) == -1)
		fd_error(cmd->args[1], *shell, "cd: ");
	getcwd(cwd, sizeof(cwd));
	update_pwds(*shell, cwd, 1);
	free(path);
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

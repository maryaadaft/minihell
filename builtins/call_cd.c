/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:55:50 by walneama          #+#    #+#             */
/*   Updated: 2026/07/08 16:00:22 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	t_env	*last_pwd;
	char	*home;

	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		last_pwd = find_env(shell, "OLDPWD");
		if (!last_pwd || !last_pwd->value)
			return (null_err_msg("minishell: cd: OLDPWD not set"));
		return (ft_strdup(last_pwd->value));
	}
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "~", 2) != 0)
		return (ft_strdup(cmd->args[1]));
	home = get_home(shell);
	if (!home)
		return (null_err_msg("minishell: cd: HOME not set"));
	return (ft_strdup(home));
}

void	ft_cd(t_cmd *cmd, t_shell **shell)
{
	char	oldcwd[PATH_MAX];
	char	newcwd[PATH_MAX];
	char	*path;

	if (cmd->args[1] && cmd->args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		(*shell)->exit_status = 1;
		return ;
	}
	path = get_cd_path(cmd, *shell);
	if (!path)
	{
		(*shell)->exit_status = 1;
		return ;
	}
	getcwd(oldcwd, sizeof(oldcwd));
	if (chdir(path) == -1)
	{
		fd_error(cmd->args[1], *shell, "cd: ");
		free(path);
		return ;
	}
	update_pwds(*shell, oldcwd, 0);
	getcwd(newcwd, sizeof(newcwd));
	update_pwds(*shell, newcwd, 1);
	free(path);
	(*shell)->exit_status = 0;
}

char *get_home(t_shell *shell)
{
	t_env *head_env;
	char *path;

	head_env = shell->env;
	path = NULL;
	while (head_env)
	{
		if (ft_strncmp(head_env->key, "HOME", 5) == 0)
		{
			path = head_env->value;
			// printf("\nhome path is :- %s\n", path);
		}
		head_env = head_env->next;
	}
	return (path);
}

void	update_pwds(t_shell *shell, char *cwd, int	flag_path)
{
	t_env *head_env;
	
	head_env = shell->env;
	while (head_env)
	{
		//old pwd is 0
		if (flag_path == 0 && ft_strncmp(head_env->key, "OLDPWD", 7) == 0)
		{
			free(head_env->value); //need to free the old value before it breaks.
			head_env->value = ft_strdup(cwd);
			// printf("\n oldpwd is :- %s\n", head_env->value);
		}
		else if (flag_path == 1 && ft_strncmp(head_env->key, "PWD", 4) == 0)
		{
			free(head_env->value); //need to free the old value before it breaks.
			head_env->value = ft_strdup(cwd);
			// printf("\n pwd is :- %s\n", head_env->value);
		}
		head_env = head_env->next;
	}
}

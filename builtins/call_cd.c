/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:55:50 by walneama          #+#    #+#             */
/*   Updated: 2026/06/20 16:52:33 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_cmd *cmd, t_shell **shell)
{
	char cwd[PATH_MAX];  // current working directory
	char *path;
	t_env *last_pwd;
	
	path = NULL;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		last_pwd = find_env(*shell, "OLDPWD");
		if (last_pwd)
			path = ft_strdup(last_pwd->value);
	}
	else if (cmd->args[1])
		path = ft_strdup(cmd->args[1]);
	else
		path = ft_strdup(get_home(*shell));
	if (!path)
		return ((void)num_err_msg("minishell: cd: OLDPWD not set"));
	getcwd(cwd, sizeof(cwd));
	update_pwds(*shell, cwd, 0);
	if (chdir(path) == -1)
		return(perror("chdir"));
	getcwd(cwd, sizeof(cwd));
	update_pwds(*shell, cwd, 1);
	free(path);
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

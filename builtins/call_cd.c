/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:55:50 by walneama          #+#    #+#             */
/*   Updated: 2026/06/06 19:37:46 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_cmd *cmd, t_shell **shell)
{
	char cwd[PATH_MAX];  // current working directory
	char *path;
	
	path = NULL;
	getcwd(cwd, sizeof(cwd));
	update_pwds(*shell, cwd, 0);
	if (cmd->args[1] != NULL)
	{
		path = cmd->args[1];
		printf("\npath is :- %s\n", path);
	}
	else
		path = get_home(*shell);
	if (!path)
		printf("\n\nwe have an errrrroooorr!!!!\n\n");
	if (chdir(path) == -1)
	{
		printf("error and free?\n");
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	update_pwds(*shell, cwd, 1); 
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
			printf("\nhome path is :- %s\n", path);
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
			head_env->value = ft_strdup(cwd);
			printf("\n oldpwd is :- %s\n", head_env->value);
		}
		else if (flag_path == 1 && ft_strncmp(head_env->key, "PWD", 4) == 0)
		{
			head_env->value = ft_strdup(cwd);
			printf("\n pwd is :- %s\n", head_env->value);
		}
		head_env = head_env->next;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 19:31:12 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/23 19:31:37 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

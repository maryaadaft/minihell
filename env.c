/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:11:23 by walneama          #+#    #+#             */
/*   Updated: 2026/06/09 22:29:49 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_init(t_shell *shell, char **envp)
{
	t_env *env_node;
	int i;
	
	i = 0;
	shell->env = NULL;
	while (envp[i] != NULL)
	{
		env_node = get_env(envp[i]);
		if (!env_node)
			return ;
		addback_env(&shell->env, env_node);
		i++;
	}
}

t_env *get_env(char *envp)
{
	t_env	*node;
	char	*equal_sign;
	
	node = malloc(sizeof(t_env));
	ft_memset(node, 0, sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(envp, '=');
	if (!equal_sign)
	{
		node->key = ft_strdup(envp);
		node->value = ft_strdup("");
	}
	else
	{
		node->key = ft_substr(envp, 0, (equal_sign - envp));
		node->value = ft_strdup(equal_sign + 1);
	}
	if (!node->key || !node->value)
	{
		free_env_node(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void addback_env(t_env **env_list, t_env *new_env)
{
	t_env	*temp;

	if (!new_env)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_env;
		return ;
	}
	temp = *env_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_env;
}

t_env *find_env(t_shell *shell, char *target)
{
	t_env	*temp;
	
	temp = shell->env;
	while (temp)
	{
		if (ft_strncmp(temp->key, target, (ft_strlen(target) + 1)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

// Claude wrote this!!!
void remove_env(t_env **env_list, const char *old_key)
{
	t_env	*temp;
	t_env	*prev;

	if (!old_key || !env_list || !*env_list)
		return ;
	prev = NULL;
	temp = *env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, old_key, ft_strlen(old_key) + 1))
		{
			if (prev)
				prev->next = temp->next;
			else
				*env_list = temp->next;
			free_env_node(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int is_builtin(char *cmd_name)
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

void run_builtin(t_cmd *cmd, t_shell *shell)
{
    if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
        ft_echo(cmd);
    else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
        ft_cd(cmd, &shell);
	else if(ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ft_pwd(cmd);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
        ft_exit(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
        ft_env(shell);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
        ft_unset(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
        ft_export(cmd, shell);
}

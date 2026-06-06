/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:11:23 by walneama          #+#    #+#             */
/*   Updated: 2026/06/06 16:42:51 by walneama         ###   ########.fr       */
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
	memset(node, 0, sizeof(t_env));
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

void ft_echo(t_cmd *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
    {
        newline = 0;
        i = 2;
    }
    while (cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        if (cmd->args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}

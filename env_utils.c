/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:20:34 by walneama          #+#    #+#             */
/*   Updated: 2026/07/24 17:02:27 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_to_str(t_env *node)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(node->key, "=");
	if (!temp)
		return (NULL);
	if (node->value)
		result = ft_strjoin(temp, node->value);
	else
		result = ft_strjoin(temp, "");
	free(temp);
	return (result);
}

char	**env_to_array(t_shell *shell)
{
	int		i;
	char	**envp;
	t_env	*temp;

	i = 0;
	temp = shell->env;
	envp = malloc(sizeof(char *) * (env_len(shell) + 1));
	if (!envp)
		return (NULL);
	while (temp)
	{
		envp[i] = env_to_str(temp);
		if (!envp[i])
		{
			free_args(envp);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	env_len(t_shell *shell)
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

void	update_env_value(t_env *node, char *value)
{
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	if (!value)
		return ;
	node->value = ft_strdup(value);
}

void	free_env(t_env **env_list)
{
	t_env	*head;
	t_env	*next;

	if (!env_list || !*env_list)
		return ;
	head = *env_list;
	while (head)
	{
		next = head->next;
		if (head->key)
		{
			free(head->key);
			head->key = NULL;
		}
		if (head->value)
		{
			free(head->value);
			head->value = NULL;
		}
		free(head);
		head = next;
	}
	*env_list = NULL;
}

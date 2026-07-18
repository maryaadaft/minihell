/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:57:01 by walneama          #+#    #+#             */
/*   Updated: 2026/07/18 12:51:01 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			return (NULL);
		}
	}
	return (new);
}



static t_env	**build_env_array(t_shell *shell, int len)
{
	t_env	**copy_env;
	t_env	*temp;
	int		i;

	copy_env = malloc(sizeof(t_env *) * (len + 1));
	if (!copy_env)
		return (NULL);
	temp = shell->env;
	i = 0;
	while (temp)
	{
		copy_env[i] = temp;
		i++;
		temp = temp->next;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

static void	sort_env(t_env **copy_env, int len)
{
	int		i;
	int		j;
	t_env	*swap;

	i = 0;
	while (i < (len - 1))
	{
		j = 0;
		while (j < (len - i - 1))
		{
			if (ft_strncmp(copy_env[j]->key, copy_env[j + 1]->key,
					ft_strlen(copy_env[j]->key) + 1) > 0)
			{
				swap = copy_env[j];
				copy_env[j] = copy_env[j + 1];
				copy_env[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_shell *shell)
{
	int		len;
	int		i;
	t_env	**s_env;

	len = env_len(shell);
	s_env = build_env_array(shell, len);
	if (!s_env)
		return ;
	sort_env(s_env, len);
	i = 0;
	while (s_env[i])
	{
		if (s_env[i]->value && s_env[i]->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", s_env[i]->key, s_env[i]->value);
		else if (s_env[i]->value && s_env[i]->value[0] == '\0')
			printf("declare -x %s=\"\"\n", s_env[i]->key);
		else
			printf("declare -x %s\n", s_env[i]->key);
		i++;
	}
	free(s_env);
}

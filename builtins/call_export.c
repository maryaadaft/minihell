/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:04:58 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/13 17:04:29 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if export only -> we write all the env in specific format ----- DONE
// if the key=value exist -> we update ----- DONE
// if key=value doesn't exist -> we add a new entry ---- DONE
// if key only without a value -> we add an entry with no value ---- DONE


//we have to sort the env before we print it, so we copy to temp and sort there. maybe split into 2 functions
t_env **sort_env(t_shell *shell, int len)
{
	t_env **copy_env;
	t_env *temp;
	t_env *swap;
	int i;
	int j;

	len = env_len(shell);
	copy_env = malloc(sizeof(t_env *) * (len + 1));
	if (!copy_env)
		return(NULL);
	temp = shell->env;
	i = 0;
	while(temp)
	{
		copy_env[i] = temp;
		i++;
		temp = temp->next;
	}
	copy_env[i] = NULL;
	i = 0;
	while (i < (len - 1))
	{
		j = 0;
		while(j < (len - i - 1))
		{
			if (ft_strncmp(copy_env[j]->key, copy_env[j+ 1]->key, ft_strlen(copy_env[j]->key) + 1) > 0)
			{
				swap = copy_env[j];
				copy_env[j] = copy_env[j + 1];
				copy_env[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
	return (copy_env);
}

static void print_export(t_shell *shell)
{
	int len;
	t_env **sorted_env;
	len = env_len(shell);
	sorted_env = sort_env(shell, len);
	if(!sorted_env)
		return ;
	int i = 0;
	while(sorted_env[i])
	{
		if (sorted_env[i]->value && sorted_env[i]->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", sorted_env[i]->key, sorted_env[i]->value);
		else if (sorted_env[i]->value && sorted_env[i]->value[0] == '\0')
			printf("declare -x %s=\"\"\n", sorted_env[i]->key);
		else
			printf("declare -x %s\n", sorted_env[i]->key);
		i++;
	}
	free(sorted_env);
	// while (temp)
	// {
	// 	if (temp->value && temp->value[0] != '\0')
	// 		printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
	// 	else if (temp->value && temp->value[0] == '\0')
	// 		printf("declare -x %s=\"\"\n", temp->key);
	// 	else
	// 		printf("declare -x %s\n", temp->key);
	// 	temp = temp->next;
	// }
}

static char *get_key(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}

static char *get_value(char *arg)
{
	char *equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if ((equal_sign && *(equal_sign + 1) == '\0'))
		return (ft_strdup(""));
	if (!equal_sign)
		return (NULL);
	return (ft_strdup(equal_sign + 1));
}

static void    update_env(t_env *node, char *value)
{
	if (node->value)
		free(node->value);
	if (!value)
		return ;
	node->value = ft_strdup(value);
}

static int is_valid_key(char *str)
{
    int i;

    i = 0;
    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void	export_add(t_shell *shell, char *key, char *value)
{
	t_env	*node;
	t_env	*new;

	node = find_env(shell, key);
	if (node)
		update_env(node, value);
	else
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return ;
		new->key = ft_strdup(key);
		if (!new->key)
		{
			free (new);
			return ;
		}
		if (value)
		{
			new->value = ft_strdup(value);
			if (!new->value)
			{
				free(new->key);
				free(new);
				return ;
			}
		}
		addback_env(&shell->env, new);
	}
}

void	ft_export(t_cmd *cmd, t_shell *shell)
{
	char	*key;
	char	*value;
	int		i;

	if (!cmd->args[1])
		return (print_export(shell));
	i = 0;
	while (cmd->args[++i])
	{
		key = get_key(cmd->args[i]);
		if (!is_valid_key(key))
		{
			write(2, "minishell: export: '", 20);
			write(2, cmd->args[i], ft_strlen(cmd->args[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		else
		{
			value = get_value(cmd->args[i]);
			export_add(shell, key, value);
			free(value);
		}
		free(key);
	}
}

// t_env **sort_env(t_shell *shell)
// {
// 	t_env **arr;
// 	t_env **temp;

// 	int len = env_len(shell);
// 	arr = malloc(sizeof(t_env *) * (len + 1));
// 	if (!arr)
// 		return(NULL);
// 	temp = shell->env;
// 	int i = 0;

// 	while(temp)
// 	{
// 		arr[i] = temp;
// 		i++;
// 		temp = temp->next;
// 	}
// 	arr[i] = NULL;
	

// 	t_env *swap;
// 	i = 0;
// 	while (i < (len - 1))
// 	{
// 		j = 0;
// 		while(j < (len - i - 1))
// 		{
// 			if (ft_strncmp(arr[j]->key, arr[j+ 1]->key, ft_strlen(arr[j]->key) + 1) > 0)
// 			{
// 				swap = arr[j];
// 				arr[j] = arr[j + 1];
// 				arr[j + 1] = swap;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }


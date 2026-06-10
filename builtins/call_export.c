/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:04:58 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/10 15:37:29 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if export only -> we write all the env in specific format ----- DONE
// if the key=value exist -> we update ----- DONE
// if key=value doesn't exist -> we add a new entry ---- DONE
// if key only without a value -> we add an entry with no value ---- DONE

static void print_export(t_cmd *cmd, t_shell *shell)
{
	t_env *temp;
	temp = shell->env;
	while (temp)
	{
		if (temp->value && temp->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else if (temp->value && temp->value[0] == '\0' && ft_strchr(cmd->args[1], '=')) // had = sign
			printf("declare -x %s=\"\"\n", temp->key);
		else
			printf("declare -x %s\n", temp->key);
		// printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
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
	if (!equal_sign)
		return (ft_strdup(""));
	return (ft_strdup(equal_sign + 1));
}

static void    update_env(t_env *node, char *value)
{
	if (node->value)
		free(node->value);
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

static void	export_error_msg(char *arg)
{
	write(2, "minishell: export: '", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

void ft_export(t_cmd *cmd, t_shell *shell)
{
	t_env *node;
	char *key;
	char *value;
	int i;

	i = 0;
	if (!cmd->args[1])
		return (print_export(cmd ,shell));
	while (cmd->args[++i])
	{
		key = get_key(cmd->args[i]);
		if (!is_valid_key(key))
			export_error_msg(cmd->args[i]);
		else
		{
			value = get_value(cmd->args[i]);
			node = find_env(shell, key);
			if (node)
				update_env(node, value);
			else
				addback_env(&shell->env, get_env(cmd->args[i]));
			free(value);
		}
		free(key);
	}
}

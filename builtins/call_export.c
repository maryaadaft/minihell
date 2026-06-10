/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:04:58 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/10 16:15:39 by walneama         ###   ########.fr       */
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
		else if (temp->value && temp->value[0] == '\0')
			printf("declare -x %s=\"\"\n", temp->key);
		else
			printf("declare -x %s\n", temp->key);
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
		new->key = ft_strdup(key);
		if (value)
			new->value = ft_strdup(value);
		addback_env(&shell->env, new);
	}
}

void	ft_export(t_cmd *cmd, t_shell *shell)
{
	char	*key;
	char	*value;
	int		i;

	if (!cmd->args[1])
		return (print_export(cmd, shell));
	i = 0;
	while (cmd->args[++i])
	{
		key = get_key(cmd->args[i]);
		if (!is_valid_key(key))
		{
			write(2, "minishell: export: '", 20);
			write(2, cmd->args, ft_strlen(*cmd->args));
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

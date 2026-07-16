/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:04:58 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/16 19:04:28 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_key(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}

static char	*get_value(char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if ((equal_sign && *(equal_sign + 1) == '\0'))
		return (ft_strdup(""));
	if (!equal_sign)
		return (NULL);
	return (ft_strdup(equal_sign + 1));
}

static int	is_valid_key(char *str)
{
	int	i;

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
		update_env_value(node, value);
	else
	{
		new = create_env_node(key, value);
		if (!new)
			return ;
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

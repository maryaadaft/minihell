/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:04:58 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/18 12:57:24 by walneama         ###   ########.fr       */
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

static int	export_arg(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;

	key = get_key(arg);
	if (!is_valid_key(key))
	{
		write(2, "minishell: export: '", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		free(key);
		return (1);
	}
	value = get_value(arg);
	export_add(shell, key, value);
	free(value);
	free(key);
	return (0);
}

void	ft_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		had_error;

	if (!cmd->args[1])
	{
		print_export(shell);
		shell->exit_status = 0;
		return ;
	}
	had_error = 0;
	i = 0;
	while (cmd->args[++i])
	{
		if(export_arg(shell, cmd->args[i]))
			had_error = 1;
	}
	shell->exit_status = had_error;
}

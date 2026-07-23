/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:16:57 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/23 16:19:45 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_shlvl(t_shell *shell)
{
	t_env	*node;
	int		lvl;

	node = find_env(shell, "SHLVL");
	if (!node || !node->value)
		return (1);
	lvl = ft_atoi(node->value);
	if (lvl < 0)
		lvl = 0;
	return (lvl + 1);
}

void	init_shlvl(t_shell *shell)
{
	t_env	*node;
	char	*new_value;

	node = find_env(shell, "SHLVL");
	new_value = ft_itoa(get_shlvl(shell));
	if (!new_value)
		return ;
	if (node)
		update_env_value(node, new_value);
	else
	{
		node = create_env_node("SHLVL", new_value);
		if (node)
			addback_env(&shell->env, node);
	}
	free(new_value);
}

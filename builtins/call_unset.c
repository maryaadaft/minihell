/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:17:39 by walneama          #+#    #+#             */
/*   Updated: 2026/07/16 19:05:57 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env(&shell->env, cmd->args[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:17:39 by walneama          #+#    #+#             */
/*   Updated: 2026/06/07 23:06:51 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int 		i;

	i = 1;
	while (cmd->args[i])
	{
		// if (shell->env)
		remove_env(&shell->env, cmd->args[i]);
		i++;
	}	
}

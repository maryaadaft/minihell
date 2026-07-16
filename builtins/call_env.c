/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:02:53 by walneama          #+#    #+#             */
/*   Updated: 2026/07/16 18:58:05 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_shell *shell)
{
	t_env	*temp;

	temp = shell->env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

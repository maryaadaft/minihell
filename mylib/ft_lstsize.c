/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:05:07 by walneama          #+#    #+#             */
/*   Updated: 2026/06/10 16:44:44 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_env *env)
{
	int	count;

	count = 0;
	if (!env)
		return (0);
	while (env != NULL)
	{
		env = env->next;
		count++;
	}
	return (count);
}

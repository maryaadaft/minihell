/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:13:45 by walneama          #+#    #+#             */
/*   Updated: 2026/07/24 17:13:57 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *str, int *pos)
{
	int	start;

	start = *pos;
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
		(*pos)++;
	return (ft_substr(str, start, (*pos - start)));
}

char	*get_env_value(t_shell *shell, char *key)
{
	t_env	*node;

	node = find_env(shell, key);
	if (node && node->value)
		return (ft_strdup(node->value));
	return (ft_strdup(""));
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*final_str;

	final_str = ft_strjoin(s1, s2);
	free(s1);
	if (!final_str)
		free(s2);
	return (final_str);
}

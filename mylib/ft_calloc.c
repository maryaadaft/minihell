/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:46:55 by walneama          #+#    #+#             */
/*   Updated: 2026/05/24 19:33:09 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;
	size_t	length;

	if (count == 0)
		return (malloc(0));
	if (size != 0 && count > (SIZE_MAX / size))
		return (NULL);
	length = size * count;
	str = malloc(length);
	if (str == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}

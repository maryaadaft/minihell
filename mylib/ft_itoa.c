/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:56:04 by walneama          #+#    #+#             */
/*   Updated: 2026/06/23 22:01:38 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	counter(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	if (n < 0)
	{
		count = 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nbr;
	char	*string;

	nbr = (long)n;
	len = counter(nbr);
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	string[len] = '\0';
	if (nbr == 0)
		string[0] = '0';
	if (nbr < 0)
	{
		string[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		string[--len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (string);
}

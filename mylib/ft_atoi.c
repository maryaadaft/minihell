/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:23:30 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/23 16:24:17 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	overflowing(long long n, int sign, char c)
{
	if (n > LLONG_MAX / 10
		|| (n == LLONG_MAX / 10 && (c - '0') > LLONG_MAX % 10))
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	n;

	sign = 1;
	n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (overflowing(n, sign, str[i]) != 1)
			return (overflowing(n, sign, str[i]));
		n = (n * 10) + str[i] - 48;
		i++;
	}
	return (n * sign);
}

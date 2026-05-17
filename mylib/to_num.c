/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:00:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/17 17:09:09 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../minishell.h"

static int	overflowing(long long n, int sign, char c, int *over_check)
{
	if (sign == 1)
	{
		if (n > INT_MAX / 10
			|| (n == INT_MAX / 10 && (c - '0') > INT_MAX % 10))
		{
			*over_check = 1;
			return (*over_check);
		}
	}
	if (sign == -1)
	{
		if (n > -(long)INT_MIN / 10
			|| (n == -(long)INT_MIN / 10 && (c - '0') > -(long)(INT_MIN % 10)))
		{
			*over_check = 1;
			return (*over_check);
		}
	}
	return (0);
}

int	to_num(const char *str, int *over_check)
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
		if (overflowing(n, sign, str[i], over_check) == 1)
			return (overflowing(n, sign, str[i], over_check));
		n = (n * 10) + str[i] - 48;
		i++;
	}
	return (n * sign);
}
*/
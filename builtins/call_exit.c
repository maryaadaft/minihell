/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:10:41 by walneama          #+#    #+#             */
/*   Updated: 2026/06/06 20:24:16 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	convert_to_int(const char *s)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	while (*s >= '0' && *s <= '9')
	{
		if (n > INT_MAX / 10
			|| (n == INT_MAX / 10 && *s - '0' > INT_MAX % 10))
		{
			return (0);
		}
		n = n * 10 + (*s++ - '0');
	}
	return ((int)(n * sign));
}

void	ft_exit(t_shell *shell, t_cmd *cmds)
{
	int exit_num;

	if (!is_valid_number(cmds->args[1]))
		write(2, "invalid exit code, please input a number\n", 42);
	exit_num = convert_to_int(cmds->args[1]);
	if (!cmds->args[1] && ft_strncmp(cmds->args[0], "exit", 5) == 0)
	{
		write(2, "exit\n", 1);
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	else if (cmds->args[1])
	{
		shell->exit_status = exit_num;
		exit(shell->exit_status);
	}
}
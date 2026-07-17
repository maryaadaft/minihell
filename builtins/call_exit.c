/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:10:41 by walneama          #+#    #+#             */
/*   Updated: 2026/07/17 22:18:59 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	convert_to_int(const char *s, int *over)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	*over = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	while (*s >= '0' && *s <= '9')
	{
		if (n > LONG_MAX / 10
			|| (n == LONG_MAX / 10 && *s - '0' > LONG_MAX % 10))
		{
			*over = 1;
			return (0);
		}
		n = n * 10 + (*s++ - '0');
	}
	return ((int)(n * sign));
}

int	ft_exit(t_shell *shell, t_cmd *cmds)
{
	int	exit_code;
	int overflow;

	write(2, "exit\n", 5);
	if (cmds->args[1] && cmds->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->exit_status = 1;
		return (1);
	}
	if (!cmds->args[1])
		exit_code = shell->exit_status;
	else if (!is_valid_number(cmds->args[1]))
		exit_error(cmds, &exit_code);
	else
	{
		exit_code = convert_to_int(cmds->args[1], &overflow);
		if (overflow)
			exit_error(cmds, &exit_code);
	}
	free_shell(shell);
	exit(exit_code);
}

void exit_error(t_cmd *cmds, int *exit_code)
{
	write(2, "minishell: exit: ", 17);
	write(2, cmds->args[1], ft_strlen(cmds->args[1]));
	write(2, ": numeric argument required\n", 28);
	*exit_code = 2;
}
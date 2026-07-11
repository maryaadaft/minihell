/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:10:41 by walneama          #+#    #+#             */
/*   Updated: 2026/06/10 14:40:56 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	convert_to_int(const char *s)
{
	unsigned long long	n;
	int					sign;

	n = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	while (*s >= '0' && *s <= '9')
		n = n * 10 + (*s++ - '0');
	if (sign < 0)
		return ((int)((256 - (n % 256)) % 256));
	return ((int)(n % 256));
}

static int	exit_arg_overflows(const char *s)
{
	int		neg;
	size_t	len;

	neg = 0;
	if (*s == '+' || *s == '-')
		neg = (*s++ == '-');
	while (*s == '0' && s[1])
		s++;
	len = ft_strlen(s);
	if (len < 19)
		return (0);
	if (len > 19)
		return (1);
	if (neg)
		return (ft_strncmp(s, "9223372036854775808", 19) > 0);
	return (ft_strncmp(s, "9223372036854775807", 19) > 0);
}

// only exit -> print exit + last exit_status
// EXIT + CODE -> PRINT EXIT + THAT CODE
// exit + invalid code (string) -> 
//      print exit + minishell: exit: wisswiss: numeric argument required + 	  set exit code to 2
// exit + too many numbers ->
//      print exit + minishell: exit: too many arguments  + doesn't exit 	+ 		set exit code = 1 

int	ft_exit(t_shell *shell, t_cmd *cmds)
{
	int exit_code;   // we have to intialize shell->exit_status in main

	write(2, "exit\n", 5);
	if (cmds->args[1] && cmds->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (!cmds->args[1])
		exit_code = shell->exit_status;
	else if (!is_valid_number(cmds->args[1])
		|| exit_arg_overflows(cmds->args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, cmds->args[1], ft_strlen(cmds->args[1]));
		write(2, ": numeric argument required\n", 28);
		exit_code = 2;	
	}
	else
		exit_code = convert_to_int(cmds->args[1]);
 	free_shell(shell);
	exit(exit_code);
}

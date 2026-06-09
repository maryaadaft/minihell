/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:10:41 by walneama          #+#    #+#             */
/*   Updated: 2026/06/09 22:34:17 by walneama         ###   ########.fr       */
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
	else if (!is_valid_number(cmds->args[1]))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:56:33 by walneama          #+#    #+#             */
/*   Updated: 2026/07/21 17:55:13 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_n(char *s)
{
	int i;

	if (s[0] != '-' || s[1] != 'n')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

void	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->args[i] && is_n(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->exit_status = 0;
}

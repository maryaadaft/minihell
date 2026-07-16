/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:01:06 by walneama          #+#    #+#             */
/*   Updated: 2026/07/16 19:05:11 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		num_err_msg("minishell: Usage: pwd (no options)");
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		num_err_msg("minishell: pwd");
		return ;
	}
	printf("%s\n", cwd);
}

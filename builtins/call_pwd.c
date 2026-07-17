/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:01:06 by walneama          #+#    #+#             */
/*   Updated: 2026/07/17 20:21:07 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmd *cmd, t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		num_err_msg("minishell: Usage: pwd (no options)");
		shell->exit_status = 2;
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		num_err_msg("minishell: pwd");
		shell->exit_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	shell->exit_status = 0;
}

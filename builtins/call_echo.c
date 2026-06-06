/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:56:33 by walneama          #+#    #+#             */
/*   Updated: 2026/06/06 18:56:49 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_cmd *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
    {
        newline = 0;
        i = 2;
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
}

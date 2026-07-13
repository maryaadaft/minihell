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

static int	is_n_flag(char *s)
{
    int j;

    if (s[0] != '-' || s[1] != 'n')
        return (0);
    j = 1;
    while (s[j] == 'n')
        j++;
    return (s[j] == '\0');
}

void ft_echo(t_cmd *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    while (cmd->args[i] && is_n_flag(cmd->args[i]))
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
}

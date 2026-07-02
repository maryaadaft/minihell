/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:37:31 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/02 16:21:58 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_heredoc(t_redir *redir)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return ;
    }
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            write(2, "minishell: warning: here-document delimited by end-of-file\n", 60);
            break ;
        }
        if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
        {
            free(line);
            break ;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    redir->heredoc_fd = fd[0];
}

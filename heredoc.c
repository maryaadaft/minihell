/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:37:31 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/05 11:18:37 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_redir *redir)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (1);
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
	return (0);
}

int prep_heredocs(t_cmd *cmd)
{
    t_redir *curr;

    curr = cmd->redirs;
    while (curr)
    {
        if (curr->type == Ty_HEREDOC)
        {
            if (ft_heredoc(curr) == -1)
                return (-1);
        }
        curr = curr->next;
    }
    return (0);
}

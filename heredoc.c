/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:37:31 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/05 18:56:34 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_redir *redir, t_shell *shell)
{
    int     fd[2];
    char    *line;
	char	*to_write;

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
		if (redir->expand)
        {
            to_write = expand_str(line, shell);
            free(line);
        }
		else
			to_write = line;
        write(fd[1], to_write, ft_strlen(to_write));
        write(fd[1], "\n", 1);
        free(to_write);
    }
    close(fd[1]);
    redir->heredoc_fd = fd[0];
	return (0);
}

int prep_heredocs(t_cmd *cmd, t_shell *shell)
{
    t_redir *curr;

    curr = cmd->redirs;
    while (curr)
    {
        if (curr->type == Ty_HEREDOC)
        {
            if (ft_heredoc(curr, shell) == -1)
                return (-1);
        }
        curr = curr->next;
    }
    return (0);
}

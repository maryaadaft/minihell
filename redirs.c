/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:45:32 by walneama          #+#    #+#             */
/*   Updated: 2026/07/16 18:16:28 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_file(t_redir *redir)
{
	if (redir->type == Ty_RE_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == Ty_RE_OUT)
		return (open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == Ty_APPEND)
		return (open(redir->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	handle_heredoc(t_redir *redir)
{
	if (redir->type != Ty_HEREDOC)
		return (0);
	if (redir->heredoc_fd != -1)
	{
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
	}
	return (1);
}

int	apply_redirs(t_redir *redirs)
{
	int	fd;

	while (redirs)
	{
		if (handle_heredoc(redirs))
		{
			redirs = redirs->next;
			continue ;
		}
		fd = open_redir_file(redirs);
		if (fd < 0)
			return (redir_error(redirs->file), -1);
		if (redirs->type == Ty_RE_OUT || redirs->type == Ty_APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (redirs->type == Ty_RE_IN)
			dup2(fd, STDIN_FILENO);
		close(fd);
		redirs = redirs->next;
	}
	return (0);
}

static int	set_fd_only(t_redir *redir)
{
	if (redir->type == Ty_RE_OUT)
		return (open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == Ty_APPEND)
		return (open(redir->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (redir->type == Ty_RE_IN)
		return (open(redir->file, O_RDONLY));
	return (-1);
}

void	apply_redir_only(t_redir *redirs, t_shell *shell)
{
	int	fd;

	while (redirs)
	{
		fd = set_fd_only(redirs);
		if (fd == -1)
			return (fd_error(redirs->file, shell, NULL));
		close(fd);
		redirs = redirs->next;
	}
	shell->exit_status = 0;
}

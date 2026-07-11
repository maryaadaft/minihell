/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:37:31 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/11 17:19:28 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_write(t_redir *redir, t_shell *shell, char *line, int fd)
{
	char	*to_write;

	if (redir->expand)
	{
		to_write = expand_str(line, shell);
		free(line);
	}
	else
		to_write = line;
	write(fd, to_write, ft_strlen(to_write));
	write(fd, "\n", 1);
	free(to_write);
}

static int	heredoc_sigint(char *line, int fd[2])
{
	free(line);
	close(fd[1]);
	close(fd[0]);
	rl_event_hook = NULL;
	g_signal = 0;
	sig_interactive();
	return (-1);
}

static int	heredoc_loop(t_redir *redir, t_shell *shell, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (heredoc_sigint(line, fd));
		if (!line)
		{
			write(2, "minishell: warning: here-document "
				"delimited by end-of-file\n", 60);
			break ;
		}
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
		{
			free(line);
			break ;
		}
		heredoc_write(redir, shell, line, fd[1]);
	}
	return (0);
}

int	ft_heredoc(t_redir *redir, t_shell *shell)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	sig_heredoc();
	g_signal = 0;
	rl_event_hook = check_sigint;
	ret = heredoc_loop(redir, shell, fd);
	if (ret == -1)
		return (-1);
	rl_event_hook = NULL;
	sig_interactive();
	close(fd[1]);
	redir->heredoc_fd = fd[0];
	return (0);
}

int	prep_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*curr;

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

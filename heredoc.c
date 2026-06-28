/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2026/06/27 00:00:00 by walneama          #+#    #+#             */
/*   Updated: 2026/06/27 00:00:00 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Build a unique temp file path: /tmp/minishell_hd_<pid>_<index> */
static char	*make_temp_name(int index)
{
	char	*pid_str;
	char	*idx_str;
	char	*name;
	char	*tmp;

	pid_str = ft_itoa(getpid());
	idx_str = ft_itoa(index);
	if (!pid_str || !idx_str)
		return (free(pid_str), free(idx_str), NULL);
	tmp = ft_strjoin("/tmp/minishell_hd_", pid_str);
	free(pid_str);
	if (!tmp)
		return (free(idx_str), NULL);
	name = ft_strjoin(tmp, idx_str);
	free(tmp);
	free(idx_str);
	return (name);
}

/* Read heredoc body line by line until the delimiter.
   If delim was quoted, the body is NOT expanded (bash rule).
   Writes content to fd. Returns 0 on success, -1 on error, -2 on Ctrl+C. */
static int	read_heredoc_body(int fd, char *delim, int quoted, t_shell *shell)
{
	char	*line;
	char	*written;

	while (1)
	{
		line = readline("> ");
		if (g_sigint) // Ctrl+C: abort the heredoc
			return (free(line), -2);
		if (!line) // EOF (Ctrl+D): end the heredoc like bash does
			break ;
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (quoted)
			written = ft_strdup(line); // no expansion
		else
			written = expand_str(line, shell);
		free(line);
		if (!written)
			return (-1);
		write(fd, written, ft_strlen(written));
		write(fd, "\n", 1);
		free(written);
	}
	return (0);
}

/* Read one heredoc into a temp file, then swap the redir's file
   from the delimiter to the temp file path. Returns 0 / -1. */
static int	process_heredoc(t_redir *redi, t_shell *shell, int index)
{
	char	*tmp_name;
	int		fd;

	tmp_name = make_temp_name(index);
	if (!tmp_name)
		return (-1);
	fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (free(tmp_name), -1);
	if (read_heredoc_body(fd, redi->file, redi->quoted, shell) == -1)
	{
		close(fd);
		unlink(tmp_name);
		free(tmp_name);
		return (-1);
	}
	// Ctrl+C during heredoc: drop it and tell the caller to abort
	if (g_sigint)
	{
		close(fd);
		unlink(tmp_name);
		free(tmp_name);
		return (-1);
	}
	close(fd);
	free(redi->file);      // free the delimiter
	redi->file = tmp_name; // now points at the temp file
	return (0);
}

/* Walk every command and read all heredocs in the parent before any fork,
   so they work in pipelines and with builtins. Returns 0 / -1. */
int	handle_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redi;
	int		index;

	index = 0;
	cmd = cmds;
	while (cmd)
	{
		redi = cmd->redirs;
		while (redi)
		{
			if (redi->type == Ty_HEREDOC)
			{
				if (process_heredoc(redi, shell, index++) == -1)
					return (-1);
			}
			redi = redi->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

/* Unlink the temp files backing any heredocs after execution. */
void	cleanup_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redi;

	cmd = cmds;
	while (cmd)
	{
		redi = cmd->redirs;
		while (redi)
		{
			if (redi->type == Ty_HEREDOC && redi->file)
				unlink(redi->file);
			redi = redi->next;
		}
		cmd = cmd->next;
	}
}

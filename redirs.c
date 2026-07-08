/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:45:32 by walneama          #+#    #+#             */
/*   Updated: 2026/07/08 13:32:43 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_error(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	perror("");
}

int	apply_redirs(t_redir *redirs)
{
	t_redir *temp;
	int		fd;

	temp = redirs;
	while (temp)
	{
		fd = -1;
		if (temp->type == Ty_RE_IN)
			fd = open(temp->file, O_RDONLY);
		else if (temp->type == Ty_RE_OUT)
			fd = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp->type == Ty_APPEND)
			fd = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (temp->type == Ty_HEREDOC)
		{
			if (temp->heredoc_fd != -1)
			{
				dup2(temp->heredoc_fd, STDIN_FILENO);
				close(temp->heredoc_fd);
				temp->heredoc_fd = -1;
			}
			temp = temp->next;
			continue ;
		}
		if (fd < 0)
		{
			redir_error(temp->file);
			return (-1);
		}
		if (temp->type == Ty_RE_OUT || temp->type == Ty_APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (temp->type == Ty_RE_IN)
			dup2(fd, STDIN_FILENO);
		close (fd);
		temp = temp->next;
	}
	return (0);
}

void run_builtin_with_redir(t_cmd *cmd, t_shell *shell)
{
	int old_stdin;
	int old_stdout;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (prep_heredocs(cmd, shell) == -1)
		shell->exit_status = 130;
	else if (apply_redirs(cmd->redirs) == 0)
		run_builtin(cmd, shell);
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdin);
	close(old_stdout);
}

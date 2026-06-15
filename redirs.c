/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:45:32 by walneama          #+#    #+#             */
/*   Updated: 2026/06/15 14:25:19 by walneama         ###   ########.fr       */
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
		if (temp->type == Ty_RE_IN)
			fd = open(temp->file, O_RDONLY);
		else if (temp->type == Ty_RE_OUT)
			fd = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp->type == Ty_APPEND)
			fd = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

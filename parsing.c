/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:28:15 by walneama          #+#    #+#             */
/*   Updated: 2026/07/11 18:25:05 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	if (!tokens || check_syntax(tokens) == 1)
		return (NULL);
	while (tokens)
	{
		new_cmd = ft_parse_cmd(&tokens);
		if (!new_cmd)
		{
			free_cmd(&cmd_list);
			return (NULL);
		}
		ft_addback_cmd(&cmd_list, new_cmd);
	}
	return (cmd_list);
}

static int	handle_word(t_cmd *cmd, t_token **tok)
{
	if (ft_args_append(&cmd->args, (*tok)->value) == -1)
	{
		free_cmd(&cmd);
		return (-1);
	}
	*tok = (*tok)->next;
	return (0);
}

static int	handle_redir(t_cmd *cmd, t_token **tok)
{
	t_redir	*new_redir;

	new_redir = ft_parse_redir(tok);
	if (!new_redir)
	{
		free_cmd(&cmd);
		return (-1);
	}
	ft_redir_addback(&cmd->redirs, new_redir);
	return (0);
}

static void	skip_pipe(t_token **tok)
{
	if (*tok && (*tok)->token_type == Ty_PIPE)
		*tok = (*tok)->next;
}

t_cmd	*ft_parse_cmd(t_token **tok)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (*tok && (*tok)->token_type != Ty_PIPE)
	{
		if (ft_is_word((*tok)->token_type))
		{
			if (handle_word(cmd, tok) == -1)
				return (NULL);
		}
		else if (ft_is_redir((*tok)->token_type))
		{
			if (handle_redir(cmd, tok) == -1)
				return (NULL);
		}
		else
		{
			free_cmd(&cmd);
			return (NULL);
		}
	}
	skip_pipe(tok);
	return (cmd);
}

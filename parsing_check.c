/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:29:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/23 16:48:01 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(t_type	type)
{
	return (type == Ty_RE_IN || type == Ty_RE_OUT
		|| type == Ty_HEREDOC || type == Ty_APPEND);
}

int	ft_is_word(t_type	type)
{
	return (type == Ty_WORD || type == Ty_Single_Q || type == Ty_Double_Q);
}

int	check_syntax(t_token *tokenaya)
{
	if (!tokenaya)
		return (0);
	if (tokenaya->token_type == Ty_PIPE)
		return (num_err_msg("minishell: syntax error near unexpected token `|'"));
	while (tokenaya)
	{
		if (tokenaya->token_type == Ty_PIPE
			&& !tokenaya->next)
			return (num_err_msg("minishell: syntax error near unexpected token `|'"));
		else if (tokenaya->token_type == Ty_PIPE
			&& tokenaya->next->token_type == Ty_PIPE)
			return (num_err_msg("minishell: syntax error near unexpected token `||'"));
		else if (ft_is_redir(tokenaya->token_type)
			&& (!tokenaya->next
				|| tokenaya->next->token_type == Ty_PIPE
				|| ft_is_redir(tokenaya->next->token_type)))
			return (num_err_msg("minishell: syntax error near unexpected token"));
		tokenaya = tokenaya->next;
	}
	return (0);
}

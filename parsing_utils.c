/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:29:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/05 13:39:07 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(t_type	type)
{
	return (type == Ty_RE_IN || type == Ty_RE_OUT
		|| type == 	Ty_HEREDOC || type == Ty_APPEND);
}

int	ft_is_word(t_type	type)
{
	return (type == Ty_WORD || type == Ty_Single_Q || type == Ty_Double_Q);

}
int	all_space(char *value)
{
	int i;

	i = 0;
	while (value[i])
	{
		if (value[i] <= 32)
			i++;
		else
			return(0); 
	}
	return (1);
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
		else if (tokenaya->token_type == Ty_PIPE
			&& ft_is_redir(tokenaya->next->token_type))
            return (num_err_msg("minishell: syntax error near unexpected token `|'")); // we still don't know if we need this or not!
		else if (ft_is_redir(tokenaya->token_type)
			&& (!tokenaya->next
				|| tokenaya->next->token_type == Ty_PIPE
				|| ft_is_redir(tokenaya->next->token_type)))
			return (num_err_msg("minishell: syntax error near unexpected token"));
		tokenaya = tokenaya->next;
	}
	return (0);
}

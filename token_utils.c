/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:31:04 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/20 19:27:42 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>'
		|| c == '<' || c == '\'' || c == '"' || c == '\n');
}

int	check_token_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>'
		|| c == '<' || c == '\n');
}

t_token	*build_word_token(t_shell *shell, char *result, char *raw, int was_quoted)
{
	t_token	*tok;

	tok = make_token(shell, Ty_WORD, result);
	if (tok)
	{
		tok->quoted = was_quoted;
		tok->raw_value = raw;
	}
	else
		free(raw);
	return (tok);
}

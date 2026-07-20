/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:07:13 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/20 19:26:40 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_word(t_shell	*shell, const char *input, int *pos)
{
	int		start;
	int		len;
	char	*word;

	start = *pos;
	while (input[*pos] && !is_delimiter(input[*pos]))
		(*pos)++;
	len = *pos - start;
	word = ft_substr(input, start, len);
	if (!word)
		malloc_exit(shell);
	return (word);
}

char	*ft_read_quoted(t_shell	*shell, const char *input, int *pos, char quote)
{
	int		start;
	int		len;
	char	*q_word;

	if (input[++(*pos)] == quote)
	{
		(*pos)++;
		q_word = ft_strdup("");
		if (!q_word)
			malloc_exit(shell);
		return (q_word);
	}
	start = *pos;
	while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	if (input[*pos] == '\0')
		return (null_err_msg("minishell: syntax error: unclosed quote"));
	len = *pos - start;
	(*pos)++;
	q_word = ft_substr(input, start, len);
	if (!q_word)
		malloc_exit(shell);
	return (q_word);
}

t_token	*ft_read_redir(t_shell	*shell, const char *input, int *pos)
{
	if (input[*pos] == '<' && (input[*pos + 1]) == '<')
	{
		(*pos) += 2;
		return (make_token(shell, Ty_HEREDOC, ft_strdup("<<")));
	}
	else if (input[*pos] == '<')
	{
		(*pos)++;
		return (make_token(shell, Ty_RE_IN, ft_strdup("<")));
	}
	else if (input[*pos] == '>' && input[*pos + 1] == '>')
	{
		(*pos) += 2;
		return (make_token(shell, Ty_APPEND, ft_strdup(">>")));
	}
	else if (input[*pos] == '>')
	{
		(*pos)++;
		return (make_token(shell, Ty_RE_OUT, ft_strdup(">")));
	}
	return (NULL);
}

static char	*process_chunk(t_shell *shell, const char *input,
							int *pos, int *was_quoted, char **raw)
{
	t_token	*chunk;
	char	*expanded;
	char	*raw_temp;

	chunk = create_next_token(shell, input, pos);
	if (!chunk)
		return (NULL);
	if (chunk->token_type == Ty_Single_Q || chunk->token_type == Ty_Double_Q)
		*was_quoted = 1;
	raw_temp = ft_strjoin(*raw, chunk->value);
	free(*raw);
	*raw = raw_temp;
	if (chunk->token_type == Ty_WORD || chunk->token_type == Ty_Double_Q)
		expanded = expand_str(chunk->value, shell);
	else
		expanded = ft_strdup(chunk->value);
	free(chunk->value);
	free(chunk);
	return (expanded);
}

t_token	*ft_read_word_token(t_shell *shell, const char *input, int *pos)
{
	char	*result;
	char	*expanded;
	char	*temp;
	char	*raw;
	int		was_quoted;

	was_quoted = 0;
	result = ft_strdup("");
	raw = ft_strdup("");
	if (!result || !raw)
		malloc_exit(shell);
	while (input[*pos] && !check_token_delimiter(input[*pos]))
	{
		expanded = process_chunk(shell, input, pos, &was_quoted, &raw);
		if (!expanded)
			return (free(result), free(raw), NULL);
		temp = ft_strjoin(result, expanded);
		free(result);
		free(expanded);
		if (!temp)
			malloc_exit(shell);
		result = temp;
	}
	return (build_word_token(shell, result, raw, was_quoted));
}

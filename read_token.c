/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:07:13 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/05 19:10:44 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_word(t_shell	*shell, const char *input, int *pos)
{
	int start;
	int len;
	char *word;

	start = *pos;
	while (input[*pos] && !is_delimiter(input[*pos]))
		(*pos)++;
	len = *pos - start;
	word = ft_substr(input, start, len);
	if (!word)
		malloc_exit(shell);
		// error_message("Error with malloc!!", 1); //free past tokens ?
	return (word);
}

char	*ft_read_quoted(t_shell	*shell, const char *input, int *pos, char quote)
{
	int start;
	int len;
	char *q_word;

	// empty quotes -> return empty string
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
	// No closing quote -> error
	if (input[*pos] == '\0')
	{
		shell->exit_status = 2;
		return (null_err_msg("minishell: syntax error: unclosed quote"));
	}
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

t_token	*ft_read_word_token(t_shell *shell, const char *input, int *pos,
		int expand)
{
	char	*result;
	char	*temp;
	char	*expanded;
	t_token	*chunk;
	t_token	*tok;
	int		was_quoted;

	was_quoted = 0;
	result = ft_strdup("");
	if (!result)
		malloc_exit(shell);
	while (input[*pos] && input[*pos] != ' ' && input[*pos] != '\t'
		&& input[*pos] != '\n' && input[*pos] != '|'
		&& input[*pos] != '<' && input[*pos] != '>')
	{
		chunk = create_next_token(shell, input, pos);
		if (!chunk)
			return (free(result), NULL);
		if (chunk->token_type == Ty_Single_Q || chunk->token_type == Ty_Double_Q)
			was_quoted = 1;
		if (expand && (chunk->token_type == Ty_WORD
				|| chunk->token_type == Ty_Double_Q))
			expanded = expand_str(chunk->value, shell);
		else
			expanded = ft_strdup(chunk->value);
		free(chunk->value);
		free(chunk);
		if (!expanded)
			return (free(result), NULL);
		temp = ft_strjoin(result, expanded);
		free(result);
		free(expanded);
		if (!temp)
			malloc_exit(shell);
		result = temp;
	}
	tok = make_token(shell, Ty_WORD, result);
	if (tok)
		tok->quoted = was_quoted;
	return (tok);
}

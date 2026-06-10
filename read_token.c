/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:07:13 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/10 14:35:10 by maryaada         ###   ########.fr       */
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

t_token	*ft_read_word_token(t_shell *shell, const char *input, int *pos)
{
	char	*result;
	char	*temp;
	t_token	*chunk_token;

	result = ft_strdup("");
	if (!result)
		malloc_exit(shell);
	while (input[*pos] && input[*pos] != ' ' && input[*pos] != '\t'
		&& input[*pos] != '\n' && input[*pos] != '|'
		&& input[*pos] != '<' && input[*pos] != '>')
	{
		chunk_token = create_next_token(shell, input, pos);
		if (!chunk_token)
		{
			free(result);
			return (NULL);
		}
		temp = ft_strjoin(result, chunk_token->value);
		free(result);
		free(chunk_token->value);
		free(chunk_token);
		if (!temp)
			malloc_exit(shell);
		result = temp;
	}
	return (make_token(shell, Ty_WORD, result));
}

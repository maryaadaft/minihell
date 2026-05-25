/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:50:30 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/25 22:48:56 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_token(t_type type, char *value)
{
	// 1. Allocate
	// 2. Fill valuee
	// 3. Return
	t_token *token;
	
	if (!value)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (null_err_msg("minishell: malloc failure"));
	token->token_type = type;
	token->value = value;
	return (token);
}

void	addback_token(t_token **head, t_token *new_token)
{
	// If its empty add the new token as first node
	// else: loop until we reach the end and then we add the new token to the end of list
	t_token	*temp;
	
	if (!new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
}

char	*ft_read_word(const char *input, int *pos)
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
		return (null_err_msg("minishell: malloc failure"));
		// error_message("Error with malloc!!", 1); //free past tokens ?
	return (word);
}

char	*ft_read_quoted(const char *input, int *pos, char quote)
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
			return (null_err_msg("minishell: malloc failure"));
		return (q_word);
	}
	start = *pos;
	while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	// No closing quote -> error
	if (input[*pos] == '\0')
		return (null_err_msg("minishell: syntax error: unclosed quote"));
		// null_err_msg ("Missing closing Quote!"); //should not kill the shell, return null and handle elsewhere
	len = *pos - start;
	(*pos)++;
	q_word = ft_substr(input, start, len);
	if (!q_word)
		return (null_err_msg("minishell: malloc failure"));
		// error_message("Error with malloc!!", 1); //free past tokens?
	return (q_word);
}

t_token	*ft_read_redir(const char *input, int *pos)
{
	if (input[*pos] == '<' && (input[*pos + 1]) == '<')
	{
		(*pos) += 2;	
		return (make_token(Ty_HEREDOC, ft_strdup("<<")));
	}
	else if (input[*pos] == '<')
	{
		(*pos)++;
		return (make_token(Ty_RE_IN, ft_strdup("<")));
	}
	else if (input[*pos] == '>' && input[*pos + 1] == '>')
	{
		(*pos) += 2;
		return (make_token(Ty_APPEND, ft_strdup(">>")));
	}
	else if (input[*pos] == '>')
	{
		(*pos)++;
		return (make_token(Ty_RE_OUT, ft_strdup(">")));
	}
	return (NULL);
}

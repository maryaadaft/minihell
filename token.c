/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:50:30 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/22 17:32:07 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_token(t_type type, char *value)
{
	// 1. Allocate
	// 2. Fill valuee
	// 3. Return
	t_token *token;
	token = malloc(sizeof(t_token));
	if (!token)
		error_message("Error with malloc!");
	token->token_type = type;
	token->value = value;
	token->next = NULL;
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
		error_message("Error with malloc!!");
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
		return (ft_strdup(""));
	}
	start = *pos;
	while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	// No closing quote -> error
	if (input[*pos] == '\0')
		error_message("Missing closing Quote!");
	len = *pos - start;
	(*pos)++;
	q_word = ft_substr(input, start, len);
	if (!q_word)
		error_message("Error with malloc!!");
	return (q_word);
}

t_token	*ft_read_redir(const char *input, int *pos)
{
	if (input[*pos] == '<' && (input[*pos + 1]) == '<')
	{
		(*pos) += 2;	
		return (make_token(Ty_HEREDOC, "<<"));
	}
	else if (input[*pos] == '<')
	{
		(*pos)++;
		return (make_token(Ty_REDIRECT_IN, "<"));
	}
	else if (input[*pos] == '>' && input[*pos + 1] == '>')
	{
		(*pos) += 2;
		return (make_token(Ty_APPEND, ">>"));
	}
	else if (input[*pos] == '>')
	{
		(*pos)++;
		printf("pos at redir: %d\n", *pos);
		return (make_token(Ty_REDIRECT_OUT, ">"));
	}
	return (NULL);
}

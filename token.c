/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:50:30 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/19 17:09:30 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_token(t_token_type type, char *value)
{
	// 1. Allocate
	// 2. Fill valuee
	// 3. Return
	t_token *token;
	token = malloc(sizeof(t_token));
	if (!token)
		error_message("Error with malloc!");
	token->type = type;
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

int is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>' || c == '<');
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

void error_message(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:50:30 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/10 14:09:25 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_token(t_shell	*shell, t_type type, char *value)
{
	// 1. Allocate
	// 2. Fill valuee
	// 3. Return
	t_token *token;
	
	if (!value)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		malloc_exit(shell);
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

t_token *create_next_token(t_shell	*shell, const char *input, int *pos)
{
    if (input[*pos] == '|')
        return ((*pos)++, make_token(shell, Ty_PIPE, ft_strdup("|")));
    if (input[*pos] == '<' || input[*pos] == '>')
        return (ft_read_redir(shell, input, pos));
    if (input[*pos] == '\'')
        return (make_token(shell, Ty_Single_Q, ft_read_quoted(shell, input, pos, input[*pos])));
	if (input[*pos] == '"')
        return (make_token(shell, Ty_Double_Q, ft_read_quoted(shell, input, pos, input[*pos])));
    return (make_token(shell, Ty_WORD, ft_read_word(shell, input, pos)));
}

t_token	*tokeniser(t_shell	*shell, const char *input)
{
	t_token	*head;
	t_token	*token;
	int	pos;

	if (!input)
		return (NULL);
	head = NULL;
	pos = 0;
	while (input[pos])
	{
		while (input[pos] == ' ' || input[pos] == '\t' || input[pos] == '\n')
			pos++;
		if (!input[pos])
			break ;
		if (input[pos] == '|' || input[pos] == '<' || input[pos] == '>')
			token = create_next_token(shell, input, &pos);
		else
			token = ft_read_word_token(shell, input, &pos);
		if (!token)
		{
			ft_free_tokens(&head);
			return (NULL);
		}
		addback_token(&head, token);
	}
	return (head);
}


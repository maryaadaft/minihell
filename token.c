/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:50:30 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/18 17:40:42 by walneama         ###   ########.fr       */
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

char	*ft_read_word(const char *input, int *pos)
{

}

void error_message(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}
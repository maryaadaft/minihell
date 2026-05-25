/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:29:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/25 16:12:37 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	invalid_redirect(char *tokeneya)
{
	
}

int	check_syntax(t_token *tokenaya)
{
	if (tokenaya->token_type == Ty_PIPE)
		return(1); //free tokens
	while (tokenaya)
	{
		if(all_space(tokenaya->value))
			return (1); //free tokenaya list that has spaces
		else if (tokenaya->token_type == Ty_PIPE && tokenaya->next->token_type == Ty_PIPE)
			num_err_msg("minishell: syntax error near unexpected token `||'");
		else if (>< >><< <> <<>> >>> <<< <>|)
	}
}
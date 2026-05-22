/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:39:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/22 12:45:41 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_message(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

//add free token();
void	ft_free_tokens(t_token **token_list)
{
	if (!token_list || !*token_list)
	return ;
	t_token *head;
	t_token *temp;
	
	while (head)
	{
		temp = head;
		free(temp);
		head = head->next;
	}
	free(head);
}

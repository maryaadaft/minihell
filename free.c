/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 21:35:18 by walneama          #+#    #+#             */
/*   Updated: 2026/06/01 21:35:48 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add free token();
void	ft_free_tokens(t_token **token_list)
{
	t_token *head;
	t_token *next;
	
	if	(!token_list || !*token_list)
		return ;
	head = *token_list;
	while (head)
	{
		next = head->next;
		if (head->value)
		{
			free(head->value);
			head->value = NULL;
		}
		free(head);
		head = next;
	}
	*token_list = NULL;
}

//incase of malloc failure
void	free_args(char **args)
{
	int w;

	if (!args)
		return ;
	w = 0;
	while (args[w])
	{
		free (args[w]);
		args[w] = NULL;
		w++;
	}
	free(args);
	args = NULL;
	// error_message("Memory Freed and exited", 0);
}

void free_redir(t_redir **redir_list)
{
	t_redir *head;
	t_redir *next;
	
	if (!redir_list || !*redir_list)
		return ;
	head = *redir_list;
	while (head)
	{
		next = head->next;
		if (head->file)
		{
			free(head->file);
			head->file = NULL;
		}
		free(head);
		head = next;
	}
	*redir_list = NULL;
}

void free_cmd(t_cmd **cmd_list)
{
	t_cmd *head;
	t_cmd *next;
	
	if (!cmd_list || !*cmd_list)
		return ;
	head = *cmd_list;
	while (head)
	{
		next = head->next;
		if (head->args)
		{
			free_args(head->args);
			head->args = NULL;
		}
		if (head->redirs)
			free_redir(&head->redirs);
		free(head);
		head = next;
	}
	*cmd_list = NULL;
}

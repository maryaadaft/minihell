/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:28:15 by walneama          #+#    #+#             */
/*   Updated: 2026/05/24 17:37:03 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_cmd(t_token **tok)
{
	char **args;
	//char ** -> ft_parse_args Ty_Word
	//struct redir ->
	//next
	t_token *head = *tok;
	t_cmd all_cmds = malloc((sizeof) * (t_cmds));

	while (head && head->token_type != Ty_PIPE)
	{
		head = head->next;
	}
	all_cmds->args = ft_parse_args();
	
	cmds = ft_parse_args;
	all_cmds->redir = ft_parse_redir();
	all_cmds->next = NULL;
	
}

char **ft_parse_args(t_token **tok)
{
	int	arg_count;
	t_token *head;
	char **cmd;

	arg_count = 0;
	head = *tok;
	while (head && head->token_type == Ty_Word)
	{
		arg_count++;
		head = head->next;
	}
	cmd = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd)
		return (NULL); //free
	arg_count = 0;
	while(*tok && (*tok)->token_type == Ty_Word)
	{
		cmd[arg_count] = ft_strdup((*tok)->value);
		if (!cmd[arg_count])
			return (NULL); //free
		*tok = (*tok)->next;
		arg_count++; 
	}
	cmd[arg_count] = NULL;
	return (cmd);
}

t_redir     *ft_parse_redir(t_token **tok)
{
	t_redir *redi;

	redi = malloc(sizeof(t_redir));
	if (!redi)
		return (NULL); //free smth later; //error with malloc
	redi->type = (*tok)->token_type;
	*tok = (*tok)->next;
	if (!*tok && (*tok)->token_type != Ty_Word)
		return (NULL); //handle frees later
	redi->file = ft_strdup((*tok)->value);
	if (!redi->file)
		return (NULL); //handle frees and error with malloc
	*tok = (*tok)->next;
	redi->next = NULL;
	return (redi);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:28:15 by walneama          #+#    #+#             */
/*   Updated: 2026/05/24 19:52:07 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_cmd(t_token **tok)
{
	t_cmd *cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL); //FREEEEEEE
	while (*tok && (*tok)->token_type != Ty_PIPE)
	{
		if ((*tok)->token_type == Ty_WORD)
		{
			cmd->args = ft_parse_args(tok);
			if (!cmd->args)
				return (NULL); //Freeeee WE MUST MUST MUST FREE
		}
		else if ((*tok)->token_type == Ty_REDIRECT_IN || (*tok)->token_type == Ty_REDIRECT_OUT  || (*tok)->token_type == Ty_HEREDOC  || (*tok)->token_type == Ty_APPEND)
		{
			cmd->redirs = ft_parse_redir(tok);
			if (!cmd->redirs)
				return (NULL); //FREEEEE WISSWISS
		}
		else
			return(NULL); //PARSING ERROR + FREEEE
	}
	if (*tok && (*tok)->token_type == Ty_PIPE)
		*tok = (*tok)->next;
	cmd->next = NULL;
	return (cmd);
}

char **ft_parse_args(t_token **tok)
{
	int	arg_count;
	t_token *head;
	char **cmd;

	arg_count = 0;
	head = *tok;
	while (head && head->token_type == Ty_WORD)
	{
		arg_count++;
		head = head->next;
	}
	cmd = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd)
		return (NULL); //free
	arg_count = 0;
	while(*tok && (*tok)->token_type == Ty_WORD)
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

	redi = ft_calloc(1, sizeof(t_redir));
	if (!redi)
		return (NULL); //free ] = ft_strdup((*smth later; //error with malloc
	redi->type = (*tok)->token_type;
	*tok = (*tok)->next;
	if (!*tok && (*tok)->token_type != Ty_WORD)
		return (NULL); //handle frees later
	redi->file = ft_strdup((*tok)->value);
	if (!redi->file)
		return (NULL); //handle frees and error with malloc
	*tok = (*tok)->next;
	redi->next = NULL;
	return (redi);
}

void	addback_cmd(t_cmd **cmd_head, t_cmd *next_cmd)
{
	t_cmd *temp;
	if (!next_cmd)
		return ;
	if (!*cmd_head)
	{
    	*cmd_head = next_cmd;
    	return ;
	}
	temp = *cmd_head;
	while(temp)
		temp = temp->next;
	temp->next = next_cmd;
}


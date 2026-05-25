/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:28:15 by walneama          #+#    #+#             */
/*   Updated: 2026/05/25 15:54:44 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ft_parse(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	if (!tokens)
		return (NULL); //FREE 
	// if (syntax_safe(tokens) == 1)
		return (NULL); //free tokens
	while (tokens)
	{
		new_cmd = ft_parse_cmd(&tokens);
		if (!new_cmd)
			return (NULL); //FREEEE
		ft_addback_cmd(&cmd_list, new_cmd);
	}
	return (cmd_list);
}
t_cmd	*ft_parse_cmd(t_token **tok)
{
	t_cmd *cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL); //FREEEEEEE
	while (*tok && (*tok)->token_type != Ty_PIPE)
	{
		if ((*tok)->token_type == Ty_WORD || (*tok)->token_type == Ty_Single_Q || (*tok)->token_type == Ty_Double_Q)
		{
			cmd->args = ft_parse_args(tok);
			if (!cmd->args)
				return (NULL); //Freeeee WE MUST MUST MUST FREE
		}
		else if ((*tok)->token_type == Ty_RE_IN || (*tok)->token_type == Ty_RE_OUT  || (*tok)->token_type == Ty_HEREDOC  || (*tok)->token_type == Ty_APPEND)
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
	int	i;
	t_token *head;
	char **cmd;

	arg_count = 0;
	i = 0;
	head = *tok;
	while (head && (head->token_type == Ty_WORD || head->token_type == Ty_Single_Q || head->token_type == Ty_Double_Q))
	{
		arg_count++;
		head = head->next;
	}
	cmd = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd)
		return (NULL); //free
	while(*tok && i < arg_count)
	{
		cmd[i] = ft_strdup((*tok)->value);
		if (!cmd[i])
			return (NULL); //free
		*tok = (*tok)->next;
		i++; 
	}
	cmd[i] = NULL;
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

void	ft_addback_cmd(t_cmd **cmd_head, t_cmd *next_cmd)
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
	while(temp->next)
		temp = temp->next;
	temp->next = next_cmd;
}


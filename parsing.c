/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:28:15 by walneama          #+#    #+#             */
/*   Updated: 2026/06/02 10:25:41 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ft_parse(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	if (!tokens || check_syntax(tokens) == 1)
		return (NULL);
	while (tokens)
	{
		new_cmd = ft_parse_cmd(&tokens);
		if (!new_cmd)
		{
			free_cmd(&cmd_list);
			return (NULL);
		}
		ft_addback_cmd(&cmd_list, new_cmd);
	}
	return (cmd_list);
}

t_cmd	*ft_parse_cmd(t_token **tok)
{
	t_cmd		*cmd;
	t_redir		*new_redir;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	while (*tok && (*tok)->token_type != Ty_PIPE)
	{
		if (ft_is_word((*tok)->token_type))
		{
			ft_args_append(&cmd->args, (*tok)->value);
			*tok = (*tok)->next;
		}
		else if (ft_is_redir((*tok)->token_type))
		{
			new_redir = ft_parse_redir(tok);
			if (!new_redir)
			{
				free_cmd(&cmd);
				return (NULL);
			}
			ft_redir_addback(&cmd->redirs, new_redir);
		}
		else
		{
			free_cmd(&cmd);
			return (NULL);
		}
	}
	if (*tok && (*tok)->token_type == Ty_PIPE)
		*tok = (*tok)->next;
	return (cmd);
}

void	ft_args_append(char ***args, char *new_arg)
{
	char	**temp_arr;
	int		i;

	i = 0;
	if (*args)
		while ((*args)[i])
			i++;
	temp_arr = malloc(sizeof(char *) * (i + 2));
	if (!temp_arr)
	{
		free(temp_arr);
		return ;
	}
	i = 0;
	if (*args)
	{
		while ((*args)[i])
		{
			temp_arr[i] = (*args)[i];
			i++;
		}
	}
	temp_arr[i] = ft_strdup(new_arg);
	if (!temp_arr[i])
		return (free(temp_arr));
	temp_arr[i + 1] = NULL;
	free(*args);
	*args = temp_arr;
}

t_redir     *ft_parse_redir(t_token **tok)
{
	t_redir *redi;

	redi = ft_calloc(1, sizeof(t_redir));
	if (!redi)
		return (NULL); //free ] = ft_strdup((*smth later; //error with malloc
	redi->type = (*tok)->token_type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->token_type != Ty_WORD)
		return (NULL); //handle frees later
	redi->file = ft_strdup((*tok)->value);
	if (!redi->file)
		return (NULL); //handle frees and error with malloc
	*tok = (*tok)->next;
	redi->next = NULL;
	return (redi);
}

void	ft_redir_addback(t_redir **head, t_redir *new_redir)
{
	t_redir	*temp;

	if (!new_redir)
		return ;

	if (!*head)
	{
		*head = new_redir;
		return ;
	}

	temp = *head;
	while (temp->next)
		temp = temp->next;

	temp->next = new_redir;
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

// // old 
// t_cmd	*ft_parse_cmd(t_token **tok)
// {
// 	t_cmd *cmd;

// 	cmd = ft_calloc(1, sizeof(t_cmd));
// 	if (!cmd)
// 		return (null_err_msg("minishell: malloc failure"));
// 	while (*tok && (*tok)->token_type != Ty_PIPE)
// 	{
// 		if ((*tok)->token_type == Ty_WORD 
// 			|| (*tok)->token_type == Ty_Single_Q 
// 			|| (*tok)->token_type == Ty_Double_Q)
// 		{
// 			cmd->args = ft_parse_args(tok);
// 			if (!cmd->args)
// 			{
// 				free(cmd);
// 				return (NULL); //Freeeee
// 			}
// 		}
// 		else if ((*tok)->token_type == Ty_RE_IN || (*tok)->token_type == Ty_RE_OUT  || (*tok)->token_type == Ty_HEREDOC  || (*tok)->token_type == Ty_APPEND)
// 		{
// 			cmd->redirs = ft_parse_redir(tok);
// 			if (!cmd->redirs)
// 				return (NULL); //FREEEEE WISSWISS
// 		}
// 		else
// 			return(NULL); //PARSING ERROR + FREEEE
// 	}
// 	if (*tok && (*tok)->token_type == Ty_PIPE)
// 		*tok = (*tok)->next;
// 	cmd->next = NULL;
// 	return (cmd);
// }

// // we dont need it anymore?!
// char **ft_parse_args(t_token **tok)
// {
// 	int		i;
// 	int		arg_count;
// 	t_token	*head;
// 	char	**cmd;

// 	i = 0;
// 	arg_count = 0;
// 	head = *tok;
// 	while (head && (head->token_type == Ty_WORD
// 			|| head->token_type == Ty_Single_Q 
// 			|| head->token_type == Ty_Double_Q))
// 	{
// 		arg_count++;
// 		head = head->next;
// 	}
// 	cmd = malloc(sizeof(char *) * (arg_count + 1));
// 	if (!cmd)
// 		return (null_err_msg("minishell: malloc failure"));
// 	while(*tok && i < arg_count)
// 	{
// 		cmd[i] = ft_strdup((*tok)->value);
// 		if (!cmd[i])
// 		{
// 			free_args(cmd);
// 			return (null_err_msg("minishell: malloc failure"));
// 		}
// 		*tok = (*tok)->next;
// 		i++; 
// 	}
// 	cmd[i] = NULL;
// 	return (cmd);
// }

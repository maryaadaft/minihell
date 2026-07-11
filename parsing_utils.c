/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 18:11:37 by walneama          #+#    #+#             */
/*   Updated: 2026/07/11 18:37:57 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_args(char **temp_arr, char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			temp_arr[i] = args[i];
			i++;
		}
	}
}

int	ft_args_append(char ***args, char *new_arg)
{
	char	**temp_arr;
	int		i;

	i = 0;
	if (*args)
		while ((*args)[i])
			i++;
	temp_arr = malloc(sizeof(char *) * (i + 2));
	if (!temp_arr)
		return (-1);
	copy_args(temp_arr, *args);
	temp_arr[i] = ft_strdup(new_arg);
	if (!temp_arr[i])
	{
		free(temp_arr);
		return (-1);
	}
	temp_arr[i + 1] = NULL;
	free(*args);
	*args = temp_arr;
	return (0);
}

t_redir	*ft_parse_redir(t_token **tok)
{
	t_redir	*redi;

	redi = ft_calloc(1, sizeof(t_redir));
	if (!redi)
		return (NULL);
	redi->heredoc_fd = -1;
	redi->type = (*tok)->token_type;
	*tok = (*tok)->next;
	if (redi->type == Ty_HEREDOC)
		redi->expand = !((*tok)->quoted);
	if (!*tok || (*tok)->token_type != Ty_WORD)
	{
		free(redi);
		return (NULL);
	}
	redi->file = ft_strdup((*tok)->value);
	if (!redi->file)
	{
		free(redi);
		return (NULL);
	}
	*tok = (*tok)->next;
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
	t_cmd	*temp;

	if (!next_cmd)
		return ;
	if (!*cmd_head)
	{
		*cmd_head = next_cmd;
		return ;
	}
	temp = *cmd_head;
	while (temp->next)
		temp = temp->next;
	temp->next = next_cmd;
}

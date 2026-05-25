/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:39:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/25 21:39:57 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//add error ret for error messages without exiting out of our shell
/*cat file.txt | grep 'error message' > out.log
	$ echo "hello
	should return an error message "Missing Quotes" and whatever exit value WITHIN OUR SHELL
*/

//add error_code as parameter for exits
void error_message(char *str, int exit_code)
{
	write(2, str, ft_strlen(str));
	exit(exit_code);
}

int num_err_msg(char *str)
{
	printf("\033[31m");
	write(2, str, ft_strlen(str));
	printf("\033[0m\n");
	return(1);
}
//error fn for returning null
void	*null_err_msg(char *str)
{
	printf("\033[31m");   
	write(2, str, ft_strlen(str));
	printf("\033[0m\n");
	return (NULL);
}

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

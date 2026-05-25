/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:39:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/25 13:42:40 by maryaada         ###   ########.fr       */
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

//error fn for returning null
void	*null_err_msg(char *str)
{
	printf("\033[31m%s\033[0m\n", str);
	return (NULL);
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

//incase of malloc failure
void	free_args(char **args)
{
	int w;

	w = 0;
	while (args[w])
	{
		free (args[w]);
		w++;
	}
	free (args);
	// error_message("Memory Freed and exited", 0);
}

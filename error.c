/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:39:03 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/10 15:35:46 by walneama         ###   ########.fr       */
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

void malloc_exit(t_shell *shell)
{
	write(2, "minishell: malloc failure\n", 26);
	ft_free_tokens(&shell->tokens);
	free_cmd(&shell->commands);
	exit(1);
}

int num_err_msg(char *str)
{
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen(str));
	write(2, "\033[0m\n", 5);
	return(1);
}
//error fn for returning null
void	*null_err_msg(char *str)
{
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen(str));
	write(2, "\033[0m\n", 5);
	return (NULL);
}

void	fd_error(char *file_name, t_shell *shell, char *extra_str)
{
	char *join_perror;
	char *first;
	if (extra_str)
	{
		first = ft_strjoin("minishell: ", extra_str);
		join_perror = ft_strjoin(first, file_name);
	}
	else
		join_perror = ft_strjoin("minishell: ", file_name);
		
	shell->exit_status = 1;
	perror(join_perror);
	if(extra_str)
		free(first);
	free(join_perror);
}

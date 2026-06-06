/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:53:11 by walneama          #+#    #+#             */
/*   Updated: 2026/06/06 18:14:03 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	pid = fork();
	if (pid == 0)
	{
		execvp(cmd->args[0], cmd->args);
		perror("execvp");
		exit(1);
	}
	waitpid(pid, &status, 0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	shell;
// 	t_token	*tokenaya;
// 	t_cmd	*cmds;
// 	t_cmd	*temp;
// 	char	*input;

// 	shell.tokens = NULL;
// 	shell.commands = NULL;
// 	while (1)
// 	{
// 		printf("\033[32m");
// 		input = readline("minishell$ ");
// 		if (!input)
// 		{
// 			rl_clear_history();
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		tokenaya = tokeniser(&shell, input);
// 		if (!tokenaya)
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		cmds = ft_parse(tokenaya);
// 		if (!cmds)
// 		{
// 			ft_free_tokens(&tokenaya);
// 			free(input);
// 			continue ;
// 		}
// 		temp = cmds;
// 		while (temp)
// 		{
// 			ft_execute(temp, envp);
// 			temp = temp->next;
// 		}
// 		free_cmd(&cmds);
// 		ft_free_tokens(&tokenaya);
// 		free(input);
// 	}
// }
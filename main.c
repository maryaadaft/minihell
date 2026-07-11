/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:51:34 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/10 15:40:06 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0; 

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell.tokens = NULL;
	shell.commands = NULL;
	shell.env = NULL;
	shell.exit_status = 0;
	env_init(&shell, envp);
	while (1)
	{
		g_signal = 0;
		sig_interactive();
		// printf("\033[1;36m");
		input = readline("\001\033[1;36m\002minishell$ \001\033[0m\002");
		if (g_signal == SIGINT)
   			shell.exit_status = 130;
		if (!input)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			break ;
		}
		if (*input)
			add_history(input);
		shell.tokens = tokeniser(&shell, input);
		if (!shell.tokens)
		{
			free(input);
			continue ;
		}
		// printf("=== TOKENS ===\n");
		// print_tokens(shell.tokens);
		shell.commands = ft_parse(shell.tokens);
		if (!shell.commands)
		{
			shell.exit_status = 2;
			ft_free_tokens(&shell.tokens);
			free(input);
			continue ;
		}
		// printf("=== COMMANDS ===\n");
		// print_cmds(shell.commands);
		// printf("======\n");
		if (shell.commands->next)
			ft_pipe(shell.commands, &shell);
		else if (shell.commands->args && shell.commands->args[0] && is_builtin(shell.commands->args[0]))
			run_builtin_with_redir(shell.commands, &shell);
		else if (shell.commands->args && shell.commands->args[0])
			ft_execute(shell.commands, &shell);
		else if (shell.commands->redirs)
    		ft_execute(shell.commands, &shell);       // when no cmds exist but redir is there > >> < 
		free_cmd(&shell.commands);
		ft_free_tokens(&shell.tokens);
		free(input);
	}
	// printf("\n\n\n\n");
	// print_env(shell.env);
	free_env(&shell.env);
	return(shell.exit_status);
}

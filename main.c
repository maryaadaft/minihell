/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:51:34 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/08 15:34:03 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0; 

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_token	*tokenaya;
	t_cmd	*cmds;
	char *input;

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
		tokenaya = tokeniser(&shell, input);
		if (!tokenaya)
		{
			free(input);
			continue ;
		}
		shell.tokens = &tokenaya;
		// printf("=== TOKENS ===\n");
		// print_tokens(tokenaya);
		// ft_expand(tokenaya, &shell);
		cmds = ft_parse(tokenaya);
		if (!cmds)
		{
			ft_free_tokens(&tokenaya);
			free(input);
			continue ;
		}
		shell.commands = &cmds;
		// printf("=== COMMANDS ===\n");
		// print_cmds(cmds);
		//
		// printf("======\n");
		if (cmds->next)
			ft_pipe(cmds, &shell);
		else if (cmds->args && cmds->args[0] && is_builtin(cmds->args[0]))
			run_builtin_with_redir(cmds, &shell);
		else if (cmds->args && cmds->args[0])
			ft_execute(cmds, &shell);
		else if (cmds->redirs)
    		ft_execute(cmds, &shell);       // when no cmds exist but redir is there > >> < 
		free_cmd(&cmds);
		ft_free_tokens(&tokenaya);
		free(input);
	}
	// printf("\n\n\n\n");
	// print_env(shell.env);
	free_env(&shell.env);
}

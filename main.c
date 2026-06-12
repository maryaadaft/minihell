/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:51:34 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/12 12:08:23 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		printf("\033[32m");
		input = readline("minishell$ ");
		// printf("\033[0m");
		if (!input)
		{
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
		cmds = ft_parse(tokenaya);
		if (!cmds)
		{
			ft_free_tokens(&tokenaya);
			free(input);
			continue ;
		}
		shell.commands = &cmds;
		printf("=== COMMANDS ===\n");
		print_cmds(cmds);
		
		printf("======\n");
		if (is_builtin(cmds->args[0]))
			run_builtin(cmds, &shell);
		else
			ft_execute(cmds, &shell);
		free_cmd(&cmds);
		ft_free_tokens(&tokenaya);
		free(input);
	}
	printf("\n\n\n\n");
	print_env(shell.env);
	free_env(&shell.env);
}

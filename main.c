/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 13:04:39 by maryaada          #+#    #+#             */
/*   Updated: 2026/07/24 15:08:18 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	init_shell(t_shell *shell, char **envp)
{
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->env = NULL;
	shell->exit_status = 0;
	env_init(shell, envp);
	init_shlvl(shell);
}

static char	*get_input(t_shell *shell)
{
	char	*input;

	g_signal = 0;
	sig_interactive();
	input = readline("\001\033[1;36m\002minishell$ \001\033[0m\002");
	if (g_signal == SIGINT)
		shell->exit_status = 130;
	return (input);
}

static void	dispatch(t_shell *shell)
{
	if (shell->commands->next)
		ft_pipe(shell->commands, shell);
	else if (shell->commands->args && shell->commands->args[0]
		&& is_builtin(shell->commands->args[0]))
		run_builtin_with_redir(shell->commands, shell);
	else if (shell->commands->args && shell->commands->args[0])
		ft_execute(shell->commands, shell);
	else if (shell->commands->redirs)
		ft_execute(shell->commands, shell);
}

static void	process_line(t_shell *shell, char *input)
{
	if (*input)
		add_history(input);
	shell->tokens = tokeniser(shell, input);
	if (!shell->tokens)
		return ;
	shell->commands = ft_parse(shell->tokens);
	if (!shell->commands)
	{
		ft_free_tokens(&shell->tokens);
		return ;
	}
	dispatch(shell);
	free_cmd(&shell->commands);
	ft_free_tokens(&shell->tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		input = get_input(&shell);
		if (!input)
		{
			write(1, "exit\n", 5);
			free_cmd(&shell.commands);
			ft_free_tokens(&shell.tokens);
			rl_clear_history();
			break ;
		}
		process_line(&shell, input);
		free(input);
	}
	free_env(&shell.env);
	return (shell.exit_status);
}

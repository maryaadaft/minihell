/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:51:34 by maryaada          #+#    #+#             */
/*   Updated: 2026/06/04 17:13:20 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokeniser(t_shell	*shell, const char *input)
{
	t_token	*head;
	t_token	*token;
	int	pos;

	if (!input)
		return (NULL);
	head = NULL;
	pos = 0;
	while (input[pos])
	{
		while (input[pos] == ' ' || input[pos] == '\t' || input[pos] == '\n')
			pos++;
		if (!input[pos])
			break ;
		token = create_next_token(shell, input, &pos);
		if (!token)
		{
			ft_free_tokens(&head);
			return (NULL);
		}
		addback_token(&head, token);
	}
	return (head);
}

t_token *create_next_token(t_shell	*shell, const char *input, int *pos)
{
    if (input[*pos] == '|')
        return ((*pos)++, make_token(shell, Ty_PIPE, ft_strdup("|")));
    if (input[*pos] == '<' || input[*pos] == '>')
        return (ft_read_redir(shell, input, pos));
    if (input[*pos] == '\'')
        return (make_token(shell, Ty_Single_Q, ft_read_quoted(shell, input, pos, input[*pos])));
	if (input[*pos] == '"')
        return (make_token(shell, Ty_Double_Q, ft_read_quoted(shell, input, pos, input[*pos])));
    return (make_token(shell, Ty_WORD, ft_read_word(shell, input, pos)));
}

int	main(int argc, char **argv)
{
	t_shell shell;
	t_token	*tokenaya;
	t_cmd	*cmds;
	char *input;

	shell.tokens = NULL;
	shell.commands = NULL;
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
		printf("=== TOKENS ===\n");
		print_tokens(tokenaya);
		cmds = ft_parse(tokenaya);
		if (!cmds)
		{
			ft_free_tokens(&tokenaya);
			free(input);
			continue ;
		}
		printf("=== COMMANDS ===\n");
		print_cmds(cmds);
		free_cmd(&cmds);
		ft_free_tokens(&tokenaya);
		free(input);
	}
}

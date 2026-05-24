/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:51:34 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/24 19:21:23 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokeniser(const char *input)
{
	t_token	*head;
	t_token	*token;
	int	pos;

	head = NULL;
	pos = 0;
	while (input[pos])
	{
		while (input[pos] == ' ' || input[pos] == '\t')
			pos++;
		if (!input[pos])
			break ;
		token = create_next_token(input, &pos);
		if (!token)
			return (ft_free_tokens(&head), NULL);
		addback_token(&head, token);
	}
	return (head);
}

t_token *create_next_token(const char *input, int *pos)
{
    if (input[*pos] == '|')
        return ((*pos)++, make_token(Ty_PIPE, "|"));
    if (input[*pos] == '<' || input[*pos] == '>')
        return (ft_read_redir(input, pos));
    if (input[*pos] == '\'')
        return (make_token(Ty_Single_Q, ft_read_quoted(input, pos, input[*pos])));
	if (input[*pos] == '"')
        return (make_token(Ty_Double_Q, ft_read_quoted(input, pos, input[*pos])));
    return (make_token(Ty_WORD, ft_read_word(input, pos)));
}

int	main(int argc, char **argv)
{
	while (1)
	{
		char *input;
		printf("\033[32m");
		input = readline("minishell$ ");
		// printf("\033[0m");
		
		// char **args = ft_split(input, ' ');
		// printf("%s\n", input);
		
		
		// TESTING
		t_token *tokenaya;
		t_cmd *cmd;
		
		int pos;
		pos = 0;

		test_print(input, tokenaya, cmd, pos);
		
		free(input);
	}
}

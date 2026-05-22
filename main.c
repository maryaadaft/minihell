/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:51:34 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/22 18:09:14 by maryaada         ###   ########.fr       */
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
		
		int pos;
		pos = 0;

		// word
		// while (input[pos] != '\0')
		// {
		// 	if (!is_delimiter(input[pos]))
		// 		tokenaya = make_token(Ty_WORD, ft_read_word(input, &pos));
		// 	pos++;
		// 	printf("token->type: %i\n", tokenaya->token_type);
		// 	printf("token->value: %s\n", tokenaya->value);
		// }

		// double_Q
		// while (input[pos] != '\0')
		// {
		// 	if (input[pos] == '"')
		// 		tokenaya = make_token(Ty_Double_Q, ft_read_quoted(input, &pos, '"'));
		// 	pos++;
		// 	printf("token->type: %i\n", tokenaya->token_type);
		// 	printf("token->value: %s\n", tokenaya->value);
		// }

		//single_Q
		// while (input[pos] != '\0')
		// {
		// 	if (input[pos] == '\'')
		// 		tokenaya = make_token(Ty_Single_Q, ft_read_quoted(input, &pos, '\''));
		// 	pos++;
		// 	printf("token->type: %i\n", tokenaya->token_type);
		// 	printf("token->value: %s\n", tokenaya->value);
		// }

		// REDIRECT
		// while (input[pos] != '\0')
		// {
		// 	if (input[pos] == '>' || input[pos] == '<')
		// 		tokenaya = ft_read_redir(input, &pos);
		// 	// no need to increment pos
		// 	printf("token->type: %i\n", tokenaya->token_type);
		// 	printf("token->value: %s\n", tokenaya->value);
		// }
		// free(input);

		// tokenaya = tokeniser(input);
		// while (tokenaya)
		// {
		// 	create_next_token(input, &pos);
		// 	printf("token->type: %i\n", tokenaya->token_type);
		// 	// printf("token->value: %s\n", tokenaya->value);
		// 	printf("token->value ascii: %d\n", tokenaya->value[0]);
		// 	// printf("we are at character: %c and pos: %d\n", input[pos], pos);
		// 	tokenaya = tokenaya->next;
		// }
		test_print(input, tokenaya, pos);
		
		free(input);
	}
}

#include "minishell.h"

void	test_print(char *input, t_token *tokenaya, int pos)
{
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

		tokenaya = tokeniser(input);
		while (tokenaya)
		{
			// create_next_token(input, &pos);
			// printf("token->type: %i\n", tokenaya->token_type);
			printf("token->value: %s\n", tokenaya->value);
			// printf("token->value ascii: %d\n", tokenaya->value[0]);
			// printf("we are at character: %c and pos: %d\n", input[pos], pos);
			tokenaya = tokenaya->next;
		}
}

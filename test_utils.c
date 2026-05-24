#include "minishell.h"

void	test_print(char *input, t_token *tokenaya, t_cmd *cmd, int pos)
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
		cmd = ft_parse_cmd(&tokenaya);
		// while (tokenaya)
		// {
			// create_next_token(input, &pos);
			// printf("token->type: %i\n", tokenaya->token_type);
			// printf("token->value: %s\n", tokenaya->value);
			// printf("token->value ascii: %d\n", tokenaya->value[0]);
			// printf("we are at character: %c and pos: %d\n", input[pos], pos);
			// tokenaya = tokenaya->next;
		// }
		while (cmd)
		{
			printf("[");
			while (cmd->args[pos] != NULL)
			{
				printf(" \"%s\" ", cmd->args[pos]);
				pos++;
			}
			printf("]");
			printf("\n");
			while (cmd->redirs != NULL)
			{
				printf("[red type: %d ]\n", cmd->redirs->type);
				printf("[red file: %s ]\n", cmd->redirs->file);
				cmd->redirs = cmd->redirs->next;
			}
			cmd = cmd->next;
			cmd = ft_parse_cmd(&tokenaya);
		}
}


// /// MADE THIS DURING TESTING PARSING (CLAUDE MADE THIS OBV)
// int	main(void)
// {
// 	char	*input;
// 	t_token	*tokens;
// 	t_cmd	*cmds;

// 	input = readline("minishell> ");
// 	tokens = tokeniser(input);
// 	printf("=== TOKENS ===\n");
// 	print_tokens(tokens);
// 	cmds = ft_parse(tokens);
// 	printf("=== COMMANDS ===\n");
// 	print_cmds(cmds);
// 	return (0);
// }

// void	print_tokens(t_token *tok)
// {
// 	while (tok)
// 	{
// 		printf("type: %d | value: %s\n", tok->token_type, tok->value);
// 		tok = tok->next;
// 	}
// }

// void	print_redirs(t_redir *redir)
// {
// 	while (redir)
// 	{
// 		printf("  redir type: %d | file: %s\n", redir->type, redir->file);
// 		redir = redir->next;
// 	}
// }

// void	print_cmds(t_cmd *cmd)
// {
//     while (cmd)
//     {
//         int i = 0;
//         while (cmd->args && cmd->args[i])  // ← is cmd->args NULL checked?
//         {
//             printf("  arg[%d]: %s\n", i, cmd->args[i]);
//             i++;
//         }
//         print_redirs(cmd->redirs);
//         cmd = cmd->next;                   // ← is cmd->next valid?
//     }
// }
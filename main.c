#include "minishell.h"

int	main(void)
{
	while (1)
	{
		char *input;

		input = readline("minishell$ ");
		printf("%s\n", input);
		free(input);
	}
}
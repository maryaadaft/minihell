#include "minishell.h"

int	main(int argc, char **argv)
{
	while (1)
	{
		char *input;
		
		input = readline("minishell$ ");
		
		// char **args = ft_split(input, ' ');
		
		// printf("%s\n", input);
		
		free(input);
	}
}

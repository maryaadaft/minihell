#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type {
	Ty_WORD,
	Ty_PIPE,
	Ty_Single_Q,
	Ty_Double_Q,
	//redir_in ?
	Ty_Redir_Out,
	//what is heredoc
	Ty_Append,
}	t_type;



typedef struct s_tokens {
	t_type	token_type;
	char	*input_word;
	struct s_tokens	*next;
}	t_tokens;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);

#endif
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
	Ty_REDIRECT_IN,
	Ty_REDIRECT_OUT,
	Ty_HEREDOC,
	Ty_APPEND,
}	t_type;



typedef struct s_token {
	t_type	token_type;
	char	*value;
	struct s_token	*next;
}	t_token;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

t_token	*make_token(t_type type, char *value);
void	addback_token(t_token **head, t_token *new_token);
char	*ft_read_word(const char *input, int *pos);
char	*ft_read_quoted(const char *input, int *pos, char quote);
t_token	*ft_read_redir(const char *input, int *pos);

int		is_delimiter(char c);
void	error_message(char *str);

#endif
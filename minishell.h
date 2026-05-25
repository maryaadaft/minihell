#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type {
	Ty_WORD,
	Ty_PIPE,
	Ty_Single_Q,
	Ty_Double_Q,
	Ty_RE_IN,
	Ty_RE_OUT,
	Ty_HEREDOC,
	Ty_APPEND,
}	t_type;

typedef struct s_token {
	t_type	token_type;
	char	*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir {
    t_type   type;
    char            *file;      // filename or heredoc delimiter
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd {
	char **args;
	t_redir	*redirs;
	struct s_cmd *next;
}	t_cmd;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);

t_token	*make_token(t_type type, char *value);
void	addback_token(t_token **head, t_token *new_token);
char	*ft_read_word(const char *input, int *pos);
char	*ft_read_quoted(const char *input, int *pos, char quote);
t_token	*ft_read_redir(const char *input, int *pos);
t_token	*tokeniser(const char *input);
t_token *create_next_token(const char *input, int *pos);

t_cmd *ft_parse(t_token *tokens);
t_cmd	*ft_parse_cmd(t_token **tok);
char **ft_parse_args(t_token **tok);
t_redir     *ft_parse_redir(t_token **tok);
void	ft_addback_cmd(t_cmd **cmd_head, t_cmd *next_cmd);

int		is_delimiter(char c);
void	error_message(char *str, int exit_code);
void	*null_err_msg(char *str);
int		num_err_msg(char *str);
void	ft_free_tokens(t_token **token_list);

//DELETE LATER -- FOR TESTING ONLY !!!!!!
// void	test_print(char *input);
void	print_tokens(t_token *tok);
void	print_redirs(t_redir *redir);
void	print_cmds(t_cmd *cmd);

#endif
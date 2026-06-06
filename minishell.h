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
# include <limits.h>

typedef enum e_type {
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
	t_type			token_type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir {
    t_type			type;
    char			*file;
    struct s_redir	*next;
}   t_redir;

typedef struct s_cmd {
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env {
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef	struct	s_shell {
	t_token		**tokens;
	t_cmd		**commands;
    t_env       *env;
    int         exit_status;
}	t_shell;

//library fns
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		is_valid_number(char *str);

//token fns
t_token	*make_token(t_shell	*shell, t_type type, char *value);
void	addback_token(t_token **head, t_token *new_token);
char	*ft_read_word(t_shell	*shell, const char *input, int *pos);
char	*ft_read_quoted(t_shell	*shell, const char *input, int *pos, char quote);
t_token	*ft_read_redir(t_shell	*shell, const char *input, int *pos);
t_token	*tokeniser(t_shell	*shell, const char *input);
t_token *create_next_token(t_shell	*shell, const char *input, int *pos);
t_token	*ft_read_word_token(t_shell *shell, const char *input, int *pos);

//parsing fns
t_cmd		*ft_parse(t_token *tokens);
t_cmd		*ft_parse_cmd(t_token **tok);
// char		**ft_parse_args(t_token **tok);
int			ft_args_append(char ***args, char *new_arg);
t_redir		*ft_parse_redir(t_token **tok);
void		ft_redir_addback(t_redir **head, t_redir *new_redir);
void		ft_addback_cmd(t_cmd **cmd_head, t_cmd *next_cmd);

int		is_delimiter(char c);
void	error_message(char *str, int exit_code);
void	*null_err_msg(char *str);
int		num_err_msg(char *str);
void	malloc_exit(t_shell *shell);
void	ft_free_tokens(t_token **token_list);
void	free_cmd(t_cmd **cmd_list);
void	free_args(char **args);
int		ft_is_redir(t_type type);
int		ft_is_word(t_type	type);
int		check_syntax(t_token *tokenaya);
void	free_env_node(t_env *node);
void	free_env(t_env **env_list);

// Envp
void	env_init(t_shell *shell, char **envp);
t_env	*get_env(char *envp);
void	addback_env(t_env **env_list, t_env *new_env);
int		is_builtin(char *cmd_name);
void run_builtin(t_cmd *cmd, t_shell *shell);

// Builtins
void	ft_echo(t_cmd *cmd);
void	ft_cd(t_cmd *cmd, t_shell **shell);
char	*get_home(t_shell *shell);
void	update_pwds(t_shell *shell, char *cwd, int	flag_path);
void	ft_pwd(t_cmd *cmd);

//DELETE LATER -- FOR TESTING ONLY !!!!!!
// void	test_print(char *input);
void	print_tokens(t_token *tok);
void	print_redirs(t_redir *redir);
void	print_cmds(t_cmd *cmd);
void	print_env(t_env *env);

void	ft_execute(t_cmd *cmd, char **envp);

#endif
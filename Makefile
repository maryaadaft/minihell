CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCs = main.c \
	mylib/ft_isalpha.c \
	mylib/ft_isdigit.c \
	mylib/ft_split.c \
	mylib/ft_substr.c \
	mylib/ft_strlen.c \
	mylib/ft_strdup.c \
	mylib/ft_calloc.c \
	mylib/ft_strjoin.c \
	mylib/ft_strchr.c \
	mylib/ft_memset.c \
	mylib/ft_strncmp.c \
	mylib/ft_itoa.c \
	mylib/ft_isalnum.c \
	mylib/is_valid_number.c \
	token.c token_utils.c error.c test_utils.c parsing.c parsing_utils.c parsing_check.c free.c redirs.c env.c execute.c execute_utils.c read_token.c expansion.c pipe.c heredoc.c signals.c env_utils.c\
	builtins/call_cd.c \
	builtins/call_echo.c \
	builtins/call_pwd.c \
	builtins/call_exit.c \
	builtins/call_env.c \
	builtins/call_unset.c \
	builtins/call_export.c \
	builtins/call_export_utils.c

OBJs = $(SRCs:.c=.o)

# READLINE = -lreadline

Name = minishell

all : $(Name)

$(Name) : $(OBJs)
	$(CC) $(CFLAGS) -o $(Name) $(OBJs) -lreadline

clean :
	rm -f $(OBJs)

fclean : clean
	rm -f $(Name)

re : fclean all

.PHONY : all clean fclean re
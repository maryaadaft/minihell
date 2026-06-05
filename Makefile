CC = cc

CFLAGs = -Wall -Wextra -Werror -g

SRCs = main.c fork.c mylib/ft_split.c mylib/ft_substr.c mylib/ft_strlen.c mylib/ft_strdup.c token.c token_utils.c error.c test_utils.c parsing.c mylib/ft_calloc.c mylib/ft_strjoin.c parsing_utils.c free.c

OBJs = $(SRCs:.c=.o)

# READLINE = -lreadline

Name = minishell

all : $(Name)

$(Name) : $(OBJs)
	$(CC) $(CFLAGs) -o $(Name) $(OBJs) -lreadline

clean :
	rm -f $(OBJs)

fclean : clean
	rm -f $(Name)

re : fclean all

.PHONY : all clean fclean re
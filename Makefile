CC = cc

CFLAGs = -Wall -Wextra -Werror

SRCs = main.c

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
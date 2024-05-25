NAME = minishell
SRC = ./src/
FILES = $(SRE)main.c\

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: $(NAME)

$(NAME): 
		$(CC) $(CFLAGS) $(FILES) -o $(NAME)

clean:
		$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
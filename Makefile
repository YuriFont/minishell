NAME = minishell
SRC = ./src/
FILES = $(SRC)main.c\
		$(SRC)utils.c

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: $(NAME)

$(NAME): 
		$(CC) $(CFLAGS) $(FILES) -o $(NAME) -lreadline

clean:
		$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
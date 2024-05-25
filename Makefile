NAME = minishell
SRC = ./src/
FILES = $(SRC)main.c\
		$(SRC)utils.c

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
LIBFT = ./libft/
LIBFT_A = $(LIBFT)libft.a

all: $(NAME)

$(NAME): 
		$(MAKE) -C $(LIBFT)
		$(CC) $(CFLAGS) $(FILES) $(LIBFT_A) -o $(NAME) -lreadline

clean:
		$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
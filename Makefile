NAME = minishell
SRC = ./src/
FILES = $(SRC)main.c\
		$(SRC)utils.c\
		$(SRC)utils_list.c\
		$(SRC)fill_struct.c\
		$(SRC)input_options.c\

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
		$(MAKE) clean -C $(LIBFT)

fclean: clean
		$(MAKE) fclean -C $(LIBFT)
		rm -rf $(NAME)
		
re: fclean all

.PHONY: all clean fclean re
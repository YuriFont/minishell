NAME = minishell
SRC = ./src/

BUILTINS = cd.c\
			echo.c\
			env.c\
			exit.c\
			export.c\
			pwd.c\
			unset.c

EXECUTOR = command_executor.c

PARSER	= analyzer.c\
			check_input.c

UTILS	= tools.c

FILES = main.c\
		utils.c\
		utils_list.c\
		fill_struct.c\
		input_options.c\
		$(addprefix builtins/, $(BUILTINS))\
		$(addprefix executor/, $(EXECUTOR))\
		$(addprefix parser/, $(PARSER))\
		$(addprefix utils/, $(UTILS))
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
LIBFT = ./libft/
LIBFT_A = $(LIBFT)libft.a

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

$(NAME): $(LIBFT_A)
		$(CC) -g $(CFLAGS) $(addprefix ./src/, $(FILES)) $(LIBFT_A) -o $(NAME) -lreadline

clean:
		$(MAKE) clean -C $(LIBFT)

fclean: clean
		$(MAKE) fclean -C $(LIBFT)
		rm -rf $(NAME)
		
re: fclean all

.PHONY: all clean fclean re
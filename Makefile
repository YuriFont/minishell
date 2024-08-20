NAME = minishell
SRC = ./src/

BUILTINS = cd.c\
			echo.c\
			env.c\
			exit.c\
			export.c\
			pwd.c\
			unset.c\
			utils_exit.c\
			utils_export.c

EXECUTOR = command_executor.c\
			execution.c\
			input_options.c\
			path_commad.c\
			make_args.c\
			ft_pipe.c

STRUCT = fill_struct.c\
			struct_input_separator.c

REDIRECT = redirect.c\
			ft_redirections.c

PROMPT = create_prompt.c\
			get_user_var.c

PARSER	= analyzer.c\
			check_input.c\
			check_input_quotes.c\
			utils_expander.c\
			check_syntax.c\
			parse.c\
			expander.c\
			remove_quotes.c

SIGNALS = handler_signals.c

UTILS	= tools.c\
			utils_env.c\
			ft_ltoa.c\
			utils.c\
			sc_utils.c\
			utils_list.c

FILES = main.c\
		$(addprefix builtins/, $(BUILTINS))\
		$(addprefix executor/, $(EXECUTOR))\
		$(addprefix parser/, $(PARSER))\
		$(addprefix utils/, $(UTILS))\
		$(addprefix signals/, $(SIGNALS))\
		$(addprefix prompt/, $(PROMPT))\
		$(addprefix redirect/, $(REDIRECT))\
		$(addprefix struct/, $(STRUCT))

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

valgrind_supression:
		valgrind --leak-check=full --tool=memcheck -s --show-leak-kinds=all --track-origins=yes --suppressions=valgrind.supp ./minishell

.PHONY: all clean fclean re

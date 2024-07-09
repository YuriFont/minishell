/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/25 15:22:22 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 15:22:22 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

# define NO_VALID_CHAR "!@#$%^&*()-+={}[]|\\:;<>,?/"
# define GREEN "\001\e[0;32m\002"
# define BLUE "\001\e[0;34m\002"
# define RESET_COLOR "\001\e[0m\002"

typedef enum e_command
{
	COMAND,
	PIPE,
	BUILTIN,
	ARGM,
	REDIRECT,
	ENV_VA,
	WORD
}						t_command;

typedef struct s_token
{
	t_command			token;
	char				*text;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env_list
{
	char				*variable;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_minishell
{
	t_env_list			*env;
	t_token				*token;
}						t_minishell;

/* utils.c */

/* utils_list.c */
t_token					*find_last_node(t_token *head);

/*check_input.c*/
int						check_input(char *input);
void					mark_tokens(t_token *token);

/* fill_struct.c */
void					fill_struct(char *input, t_token **data);

/* env */
void					free_list(t_token *list);
void					free_env(t_env_list *list);

int						check_builtins(t_token *token, t_env_list **env);
void					check_commands(t_token *token, t_env_list **env);
void					read_command(t_token *token, t_env_list *env);

void					print_env_list(t_env_list *list);
char					*get_value_in_variable(char *variable,
							t_env_list *list);
char					*change_value_of_variable(char *new_value,
							char *variable);
t_env_list				*get_envp(void);
t_env_list				*get_in_env(char *search, t_env_list *list);
t_env_list				*find_last_node_in_env(t_env_list *head);
void					add_new_variable(t_env_list *env, char *variable,
							char *value);

/* cd */

void					change_directory(t_token *directory, t_env_list *env);

/* echo */

/* echo imprime tudo que esta entre aspas
da forma que foi dado como entrada. A split está atrapalhando */

void					print_echo(t_token *token);
/* export */

void					insert_in_env(t_env_list *env, t_token *token);

void					remove_variable_env(t_token *node, t_env_list **env);

char					**env_to_matriz(t_env_list *list);
void					print_matriz(char **matriz);
void					free_matriz(char **matriz);
int						find_next_char(int i, char c, char *input);
int						add_word(char *input, int start, t_token **data);

#endif
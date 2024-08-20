/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:45:49 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/20 10:16:55 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
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
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	ENV_VA,
	WORD
}						t_command;

typedef struct s_minishell	t_minishell;

typedef struct s_token
{
	t_command			token;
	int					fd_in;
	int					fd_out;
	char				*text;
	struct s_token		*next;
	struct s_token		*prev;
	struct s_minishell	*mini;
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
	int 				my_pid;
	int					fd_bk_in;
	int					fd_bk_out;
}						t_minishell;

/* utils.c */

/* utils_list.c */
t_token		*find_last_node(t_token *head);
/* fill_struct.c */
void		fill_struct(char *input, t_token **data);
void		append_node(char *input, t_token **data);
int			add_double_quotes(char *input, int start, t_token **data);
int			add_sigle_quotes(char *input, int start, t_token **data);
int			add_word(char *input, int start, t_token **data);
int			add_pipe(char *input, int start, t_token **data);
int			add_redirect(char *input, int start, t_token **data);

/*check_input.c*/
int			check_input(char *input);
void		mark_tokens(t_token *token);
int			check_syntax(t_token *token);

/* env */
void		free_list(t_token *list);
void		free_env(t_env_list *list);

int			check_builtins(t_token *token, t_env_list **env);
void		exe_commands(t_minishell *mini);
void		read_command(t_token *token, t_env_list *env);

void		print_env_list(t_env_list *list);
char		*get_value_in_variable(char *variable, t_env_list *list);
char		*change_value_of_variable(char *new_value, char *variable);
t_env_list	*get_envp(void);
t_env_list	*get_in_env(char *search, t_env_list *list);
t_env_list	*find_last_node_in_env(t_env_list *head);
void		add_new_variable(t_env_list *env, char *variable, char *value);

/* cd */

void		change_directory(t_token *directory, t_env_list *env);

/* echo */

/* echo imprime tudo que esta entre aspas
da forma que foi dado como entrada. A split está atrapalhando */

void		print_echo(t_token *token);
/* export */

void		insert_in_env(t_env_list *env, t_token *token);

void		remove_variable_env(t_token *node, t_env_list **env);

char		**env_to_matriz(t_env_list *list);
void		print_matriz(char **matriz);
void		free_matriz(char **matriz);

/* handler signals */
void		signal_handler(int signal);
void		handler_signals(void);
void		handle_if_signal(int status);

/* create args */

char		**create_args(char *command, t_token *token);
char		**create_args_options(char *command, t_token *token);

char		*get_path_command(t_token *token, char *paths);

/* prompt */
char		*create_prompt(t_env_list *env);
char		*get_username(t_env_list *env);
char		*get_host_name(t_env_list *env);
char		*get_new_host(char *host);
char		*get_new_username(char *name);

void		exe_exit(t_token *token, t_env_list *env, char *prompt,
				int is_command);
int			verify_exit_is_numeric(t_token *token);
void		exec_exit_is_not_numeric(t_token *token);
void		exec_exit_is_many_arguments(t_token *token);

int			verify_nome_of_variable_is_valid(char *name);
void		change_value_of_env(t_env_list *env, char *variable_change);

int			parse(char *input, char *prompt, t_minishell *mini);
int			check_quotes(char *input);
int			redirection(t_token *token);
int			get_fd(t_token *token);
void		exe_pwd(t_token *token);
void		expander_va(t_minishell *mini);
int			break_point_quotes(char c);
int			find_next_char(int i, char c, char *input);
int			verify_node_expander(char *text);
int			find_dollar(char *text, int i);
void		remove_quotes(t_token *token);
void		redirection_out(t_token *temp);
void		redirection_append(t_token *temp);
void		redirection_in(t_token *temp, int in);
void		close_fds(t_token *token, int in, int out);
int			exit_status_repository(int exit_status);
char		*get_value_of_exit(void);
int			mini_atoi(char *number);
char		*ft_ltoa(long long n);
int			get_my_pid(void);
int			everything_is_space(char *input);
char		*get_value_of_exit(void);
void		heredoc(t_token *temp, int hd);
int			break_point_quotes(char c);
int			redirect_in(t_token *token);
t_token		*first_token(t_token *token);
int			ls_pipe_first(int prev_fdin, int is_error, t_token *token, t_env_list **env);
int 		ls_pipe_second(int prev_fdin, int *status, int pid);
int			new_minishell(t_token *token, int *fd, int prev_fdin, t_env_list **env);
void		command_pipe(int *fd, int prev_fdin, t_token *token, t_env_list **env);
int			next_pipe(int *fd, int prev_fdin, t_token *token, t_env_list **env);
void		exe_this(t_token *temp, t_env_list **env, int is_pipe);
int			exe_pipe(t_token *token, t_env_list **env, int prev_fdin);
int			has_redirect_out(t_token *token);

#endif
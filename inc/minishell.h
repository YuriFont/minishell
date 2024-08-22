/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:45:49 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/21 21:12:56 by yufonten         ###   ########.fr       */
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
	WORD,
	NOT_EXIST
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
	int					my_pid;
	int					fd_bk_in;
	int					fd_bk_out;
}						t_minishell;

//Builtin:
//cd.c
int			move_to_old_directory(t_env_list *aux);
int			verify_direction(t_token *directory,
				t_env_list *env, t_env_list *aux, char *old_dir);
int			move_to_directory(t_token *directory, t_env_list *env);
void		change_directory(t_token *directory, t_env_list *env);

//echo.c
void		print_with_echo(t_token *token);
void		print_echo(t_token *token);

//env.c
void		print_env_list(t_env_list *list);
t_env_list	*get_in_env(char *search, t_env_list *list);
char		*get_value_in_variable(char *variable, t_env_list *list);
char		*change_value_of_variable(char *new_value, char *variable);
void		add_new_variable(t_env_list *env, char *variable, char *value);

//exit.c
int			is_overflow(long long exit_code, char *number);
void		exit_with_arguments(t_token *token);
void		exe_exit(t_token *token, t_env_list *env,
				char *prompt, int is_command);

//export.c
char		*get_name_of_variable(char *variable);
char		*valid_new_variable(char *new_variable);
int			verify_exist_in_env(char *name, t_env_list *env, t_token *token);
void		print_export(t_env_list *env);
void		insert_in_env(t_env_list *env, t_token *token);

//pwd.c
void		exe_pwd(t_token *token);

//unset.c
int			is_end_of_variable(char *variable, t_env_list *node);
int			is_this_node(t_env_list *temp, char *variable);
void		remove_variable_env(t_token *node, t_env_list **env);

//utils_exit.c
int			verify_exit_is_numeric(t_token *token);
void		exec_exit_is_not_numeric(t_token *token);
void		exec_exit_is_many_arguments(t_token *token);

//utils_export.c
int			verify_nome_of_variable_is_valid(char *name);
void		change_value_of_env(t_env_list *env, char *variable_change);

//Executor:
//command_executor.c
void		execute_command(char *command, char *path_command, char **argv,
				char **env);
int			is_absolute_path(t_token *token, t_env_list *list);
int			is_current_directory(t_token *token, t_env_list *list);
void		run_command(t_token *token, t_env_list *env, char *path);
void		read_command(t_token *token, t_env_list *list);

//execution.c
void		close_fds(t_token *token, int in, int out);
t_token		*find_command(t_token *token);
void		exe_this(t_token *temp, t_env_list **env, int is_pipe);
int			exe_pipe(t_token *token, t_env_list **env, int prev_fdin);
void		exe_commands(t_minishell *mini);

//ft_pipe.c
int			ls_pipe_first(int prev_fdin,
				t_token *token, t_env_list **env);
int			ls_pipe_second(int prev_fdin, int *status, int pid);
int			new_minishell(t_token *token, int *fd,
				int prev_fdin, t_env_list **env);
void		command_pipe(int *fd, int prev_fdin, t_token *token,
				t_env_list **env);
int			next_pipe(int *fd, int prev_fdin, t_token *token, t_env_list **env);

//input_options.c
int			get_fd(t_token *token);
int			check_builtins(t_token *token, t_env_list **env);

//make_args.c
int			count_of_args(t_token *list);
char		**elaborating_args(t_token *token, char *command);
char		**create_args_options(char *command, t_token *token);
char		**create_args(char *command, t_token *token);

//path_command.c
char		*get_path_command(t_token *token, char *paths);

//utils_execution.c
t_token		*next_command(t_token *token);
int			has_redirect_out(t_token *token);
int			has_pipe(t_token *token);
t_token		*first_token(t_token *token);

//Parser:
//analyzer.c
int			is_redirect(t_token *token);
int			is_command(t_token *token);
int			set_builtin(t_token *token, int has_command);
void		mark_tokens(t_token *token);

//check_input_quotes.c
int			check_if_is_quotes(char c, int *single, int *doubleq);
int			check_if_is_inside_of_quotes(int i, int *double_quotes,
				int *single_quotes, char *input);
int			check_quotes(char *input);

//check_input.c
int			check_amount_redirect(char *input, char redirect);
int			check_redirect(char *input);
int			check_input(char *input);

//check_syntax.c
int			valid_redirect(t_token *token);
int			valid_pipe(t_token *token);
void		mark_args_of_redirect(t_token *token);
int			check_syntax(t_token *token);

//expander.c
char		*get_variable(char *text, int i, t_env_list *env);
char		*get_prev_content(char *result, char *text, int *i, int expande_everything);
int			get_next_content_after_expander(char *text, int *i);
char		*expander_node(char *text, t_env_list *env, int expande_everything);
void		expander_va(t_minishell *mini);

//parse.c
int			checker_parse(t_minishell *mini);
void		direct_mini(t_minishell *mini);
int			parse(char *input, char *prompt, t_minishell *mini);

//remove_quotes.c
void		find_quotes(char *text);
int			count_char_without_quotes(char *text);
char		*copy_new_text(char *text, char *new);
char		*new_text_without_quotes(char *text);
void		remove_quotes(t_token *token);

//utils_expander.c
int			verify_node_expander(char *text);
int			find_dollar(char *text, int i, int expande_everything);

//Prompt:
//create_prompt.c
char		*organize_prompt(char *host, char *name, char *dir);
char		*create_prompt(t_env_list *env);

//get_user_var.c
char		*get_local_of_session(char *host);
char		*get_host_name(t_env_list *env);
char		*get_username(t_env_list *env);
char		*get_new_host(char *host);
char		*get_new_username(char *name);

//Redirect:
//ft_rediretions.c
void		redirection_in(t_token *temp);
void		write_in_heredoc(char *input, int fd_hd, t_env_list *env);
void		heredoc(t_token *temp);
void		redirection_out(t_token *temp);
void		redirection_append(t_token *temp);

//redirect.c
int			redirect_out(t_token *token);
int			error_redirect_in(t_token *temp, int *error);
int			redirect_in(t_token *token);
int			redirection(t_token *token);

//Signals
//handler_signals.c
void		signal_handler(int signal);
void		handler_signals(void);
void		handle_if_signal(int status);

//Struct:
//fill_struct.c
void		fill_struct(char *input, t_token **data);

//struct_input_separator.c
int			add_double_quotes(char *input, int start, t_token **data);
int			add_sigle_quotes(char *input, int start, t_token **data);
int			add_word(char *input, int start, t_token **data);
int			add_pipe(char *input, int start, t_token **data);
int			add_redirect(char *input, int start, t_token **data);

//Utils:
//ft_ltoa.c
int			count_size(long long n);
long long	ft_abs(long long n);
char		*ft_ltoa(long long n);

//sc_utils.c
int			break_point_quotes(char c);
int			find_last_caracter(char *input, int i);

//tools.c
void		free_matriz(char **matriz);
int			exit_status_repository(int exit_status);
char		*get_value_of_exit(void);
int			mini_atoi(char *number);

//utils_env.c
t_env_list	*get_envp(void);
int			count_variables_in_env(t_env_list *list);
char		**create_matriz(t_env_list *list, int size_list);
char		**env_to_matriz(t_env_list *list);

//utils_list.c
t_token		*find_last_node(t_token *head);
t_env_list	*find_last_node_in_env(t_env_list *head);
void		append_node(char *input, t_token **data);

//utils.c
void		free_list(t_token *list);
void		free_env(t_env_list *list);
int			get_my_pid(void);
int			everything_is_space(char *input);
int			find_next_char(int i, char c, char *input);

#endif
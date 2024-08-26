/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:08:27 by erramos           #+#    #+#             */
/*   Updated: 2024/08/26 20:18:23 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_command(char *command, char *path_command, char **argv,
		char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (execve(path_command, argv, env) == -1)
		{
			ft_fprintf(2, "%s: command not found\n", command);
			exit(127);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		exit_status_repository(WEXITSTATUS(status));
		handle_if_signal(status);
	}
}

int	is_absolute_path(t_token *token, t_env_list *list)
{
	char	**argv;
	char	**env;
	t_token	*temp;

	temp = token;
	if (temp->text[0] != '/')
		return (0);
	argv = create_args_options(temp->text, temp->next);
	env = env_to_matriz(list);
	execute_command(temp->text, temp->text, argv, env);
	free_matriz(env);
	free_matriz(argv);
	return (1);
}

int	is_directory(t_token *token)
{
	struct stat	st;

	if (!((token->text[0] == '.' && token->text[1] == '/')
			|| token->text[ft_strlen(token->text) - 1] == '/'))
		return (0);
	if (stat(token->text, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_fprintf(2, "-mini: %s: Is a directory\n", token->text);
			exit_status_repository(126);
			return (1);
		}
	}
	else
	{
		ft_fprintf(2, "-mini: %s No such file or directory\n", token->text);
		exit_status_repository(127);
		return (1);
	}
	return (0);
}

int	is_current_directory(t_token *token, t_env_list *list)
{
	char	**argv;
	char	**env;
	t_token	*temp;

	temp = token;
	if (is_directory(temp))
		return (1);
	if (temp->text[0] != '.' && temp->text[1] != '/')
		return (0);
	argv = create_args_options(temp->text, temp->next);
	env = env_to_matriz(list);
	execute_command(temp->text, temp->text, argv, env);
	free_matriz(env);
	free_matriz(argv);
	return (1);
}

void	run_command(t_token *token, t_env_list *env, char *path)
{
	char	**argv;
	char	**env_mat;

	argv = create_args(token->text, token->next);
	env_mat = env_to_matriz(env);
	execute_command(token->text, path, argv, env_mat);
	free_matriz(argv);
	free_matriz(env_mat);
}

void	read_command(t_token *token, t_env_list *list)
{
	char	*path;
	char	*path_command;

	if (is_absolute_path(token, list))
		return ;
	if (is_current_directory(token, list))
		return ;
	path = get_value_in_variable("PATH", list);
	if (!path)
		return (print_command_not_found(token->text));
	path_command = get_path_command(token, path);
	if (!path_command)
		return (print_command_not_found(token->text));
	run_command(token, list, path_command);
	free(path_command);
}

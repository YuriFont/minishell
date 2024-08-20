/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:49:06 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/13 14:49:06 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds(t_token *token, int in, int out)
{
	while (token)
	{
		if (token->fd_in != STDIN_FILENO && in)
		{
			dup2(token->mini->fd_bk_in, STDIN_FILENO);
			if (close(token->fd_in) == -1)
				printf("Error close fdin :%d\n", token->fd_in);
			token->fd_in = 0;
			close(token->mini->fd_bk_in);
		}
		if (token->fd_out != STDOUT_FILENO && out)
		{
			dup2(token->mini->fd_bk_out, STDOUT_FILENO);
			if (close(token->fd_out) == -1)
				printf("Error close fdout :%d\n", token->fd_out);
			token->fd_out = 1;
			close(token->mini->fd_bk_out);
		}
		token = token->next;
	}
	unlink(".heredoc");
}

int	has_pipe(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->token == PIPE)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_token	*first_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp->prev)
	{
		temp = temp->prev;
	}
	return (temp);
}

t_token	*find_command(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->token == COMAND)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	executa_isso(t_token *temp, t_env_list **env, int is_pipe)
{
	t_token	*cmd;

	if (is_pipe)
	{
		if (redirection(temp))
			return ;
	}
	cmd = find_command(temp);
	if (cmd)
	{
		if (!check_builtins(cmd, env))
			read_command(cmd, *env);
	}
	close_fds(first_token(temp), 1, 1);
}

t_token	*next_command(t_token *token)
{
	while (token)
	{
		if (token->token == PIPE)
			return (token->next);
		token = token->next;
	}
	return (token);
}

int	has_redirect_out(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == REDIRECT_OUT)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	execute_pipe(t_token *token, t_env_list **env, int prev_fdin)
{
	int	fd[2];
	int	pid;
	int	status;
	int	is_error;

	is_error = redirection(token);
	if (next_command(token) == NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (prev_fdin != 0)
			{
				dup2(prev_fdin, STDIN_FILENO);
			}
			if (close(prev_fdin) == -1)
				fprintf(stderr, "Error depois :%d\n", prev_fdin);
			if (!is_error)
				executa_isso(token, env, 0);
			free_env(*env);
			free_list(first_token(token));
			exit(exit_status_repository(-1));
		}
		else
		{
			if (close(prev_fdin) == -1)
				fprintf(stderr, "Error depois :\n");
			waitpid(pid, &status, 0);
			exit_status_repository(WEXITSTATUS(status));
			return (exit_status_repository(-1));
		}
	}
	if (pipe(fd) == -1)
		perror("error ao criar pipe\n");
	pid = fork();
	if (pid == 0)
	{
		if ((ft_strncmp(token->text, "./minishell", 12) == 0)
			|| has_redirect_out(token))
		{
			close(fd[1]);
			close(fd[0]);
			if (prev_fdin != 0)
				close(prev_fdin);
			executa_isso(token, env, 0);
			free_env(*env);
			free_list(first_token(token));
		}
		else
		{
			if (close(fd[0]) == -1)
				fprintf(stderr, "Error depois :\n");
			if (prev_fdin != 0)
			{
				dup2(prev_fdin, STDIN_FILENO);
				if (close(prev_fdin) == -1)
					fprintf(stderr, "Error depois :\n");
			}
			dup2(fd[1], STDOUT_FILENO);
			if (close(fd[1]) == -1)
				fprintf(stderr, "Error depois :\n");
			if (!is_error)
				executa_isso(token, env, 0);
			free_env(*env);
			free_list(first_token(token));
		}
		exit(1);
	}
	else
	{
		close(fd[1]);
		if (prev_fdin != 0)
		{
			if (close(prev_fdin) == -1)
				fprintf(stderr, "Error depois :%d\n", prev_fdin);
		}
		status = execute_pipe(next_command(token), env, fd[0]);
		while (waitpid(-1, NULL, WNOHANG) != -1)
			;
		return (exit_status_repository(-1));
	}
}

void	exe_commands(t_minishell *mini)
{
	int		have_pipe;
	t_token	*temp;
	int		pid;
	int		status;

	temp = mini->token;
	have_pipe = has_pipe(temp);
	if (have_pipe)
	{
		pid = fork();
		if (pid == 0)
		{
			status = execute_pipe(temp, &mini->env, 0);
			free_env(mini->env);
			free_list(first_token(temp));
			exit(exit_status_repository(-1));
		}
		else
		{
			waitpid(pid, &status, 0);
			exit_status_repository(WEXITSTATUS(status));
		}
		return ;
	}
	executa_isso(temp, &mini->env, 1);
}

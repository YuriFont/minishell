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

void	exe_this(t_token *temp, t_env_list **env, int is_pipe)
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

int	exe_pipe(t_token *token, t_env_list **env, int prev_fdin)
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
			exit(ls_pipe_first(prev_fdin, is_error, token, env));
		else
			return (ls_pipe_second(prev_fdin, &status, pid));
	}
	if (pipe(fd) == -1)
		perror("error ao criar pipe\n");
	pid = fork();
	if (pid == 0)
	{
		if (!new_minishell(token, fd, prev_fdin, env))
			command_pipe(fd, prev_fdin, token, env, is_error);
		exit(1);
	}
	else
		return (next_pipe(fd, prev_fdin, token, env));
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
			status = exe_pipe(temp, &mini->env, 0);
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
	exe_this(temp, &mini->env, 1);
}

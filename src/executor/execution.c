/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/13 14:49:06 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/13 14:49:06 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	close_fds(t_token *token)
{
	while (token)
	{
		if (token->fd_in != STDIN_FILENO)
		{
			dup2(token->fd_bk, STDIN_FILENO);
			close(token->fd_in);
			close(token->fd_bk);
		}
		if (token->fd_out != STDOUT_FILENO)
		{
			dup2(token->fd_bk, STDOUT_FILENO);
			close(token->fd_out);
			close(token->fd_bk);
		}
		token = token->next;
	}
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

void	executa_isso(t_token *temp, t_env_list **env)
{
	if (redirection(temp))
		return ;
	if (!check_builtins(temp, env))
	{
		read_command(temp, *env);
	}
	close_fds(temp);
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

void execute_pipe(t_token *token, t_env_list **env, int prev_fdin)
{
	int fd[2];
	int pid;
	int	status;

	if (next_command(token) == NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (prev_fdin != 0) 
			{
				dup2(prev_fdin, STDIN_FILENO);
				close(prev_fdin);
			}
			executa_isso(token, env);
			read_command(token, *env);
			exit(1);
		}
		else
		{
			close(prev_fdin);
			waitpid(pid, &status, 0);
			// exit(status);
			return ;
		}
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (prev_fdin != 0)
		{
			dup2(prev_fdin, STDIN_FILENO);
			close(prev_fdin);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		executa_isso(token, env);
		//read_command(token, *env);
		exit(1);
	}
	else
	{
		close(fd[1]);
		if (prev_fdin != 0)
			close(prev_fdin);
		execute_pipe(next_command(token), env, fd[0]);
		waitpid(pid, &status, 0);
		return ;
	}
}

void	exe_commands(t_token *token, t_env_list **env)
{
	int		have_pipe;
	t_token	*temp;
	int pid;
	int status;

	temp = token;
	have_pipe = has_pipe(token);
	if (have_pipe)
	{
		pid = fork();
		if (pid == 0)
			execute_pipe(token, env, 0);
		else
			while (waitpid(-1, &status, WNOHANG) != -1) ;
		return ;
	}
	(void)have_pipe;
	while (temp)
	{
		if (redirection(temp))
			return ;
		if (!check_builtins(token, env))
		{
			pid = fork();
			if (pid == 0)
				read_command(token, *env);
			waitpid(pid, &status, 0);
		}
		close_fds(temp);
	//	temp = next_command(temp);
	}
}

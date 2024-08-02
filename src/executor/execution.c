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

void	executa_isso(t_token *temp, t_env_list **env, int is_pipe)
{
	if (is_pipe)
	{
		if (redirection(temp))
			return ;
	}
	if (temp && !(temp->token > 3 && temp->token < 8) && temp->token != PIPE)
	{
		if (!check_builtins(temp, env))
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

int has_redirect_out(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == REDIRECT_OUT)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int execute_pipe(t_token *token, t_env_list **env, int prev_fdin)
{
	int fd[2];
	int pid;
	int	status;

	if (next_command(token) == NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			redirection(token);
			if (prev_fdin != 0)
			{
				dup2(prev_fdin, STDIN_FILENO);
			}
			close(prev_fdin);
			executa_isso(token, env, 0);
			exit(exit_status_repository(-1));
		}
		else
		{
			close(prev_fdin);
			waitpid(pid, &status, 0);
			// exit(WEXITSTATUS(status));
			return (WEXITSTATUS(status));
		}
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if ((ft_strncmp(token->text, "./minishell", 12) == 0))
		{
			close(fd[1]);
			close(fd[0]);
			if (prev_fdin != 0)
				close(prev_fdin);
			executa_isso(token, env, 0);
		}
		else
		{
			redirection(token);
			close(fd[0]);
			if (prev_fdin != 0)
			{
				dup2(prev_fdin, STDIN_FILENO);
				close(prev_fdin);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			executa_isso(token, env, 0);
		}
		exit(1);
	}
	else
	{
		close(fd[1]);
		if (prev_fdin != 0)
			close(prev_fdin);
		status = execute_pipe(next_command(token), env, fd[0]);
		exit_status_repository(status);
		while (waitpid(-1, NULL, WNOHANG) != -1) ;
		return (exit_status_repository(-1));
	}
}

void	exe_commands(t_minishell	*mini)
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
			execute_pipe(temp, &mini->env, 0);
			exit(exit_status_repository(-1));
		}
		else
		{
			while (waitpid(-1, &status, WNOHANG) != -1) ;
			exit_status_repository(WEXITSTATUS(status));
		}
		if (get_my_pid() != mini->my_pid)
			exit(WEXITSTATUS(status));
		return ;
	}
	// while (temp)
	// {
	 executa_isso(temp, &mini->env, 1);
		// if (redirection(temp))
		// 	return ;
		// if (!check_builtins(token, env))
		// {
		// 	pid = fork();
		// 	if (pid == 0)
		// 		read_command(token, *env);
		// 	waitpid(pid, &status, 0);
		// }
		// close_fds(temp);
	//	temp = next_command(temp);
//	}
}

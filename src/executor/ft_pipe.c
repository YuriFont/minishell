/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:09:29 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/20 09:09:29 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_redirect_in(t_token *node)
{
	t_token	*temp;

	temp = node;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == REDIRECT_IN || temp->token == HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	ls_pipe_first(int prev_fdin, t_token *token, t_env_list **env)
{
	if (prev_fdin != 0)
	{
		if (!has_redirect_in(token))
			dup2(prev_fdin, STDIN_FILENO);
	}
	if (close(prev_fdin) == -1)
		fprintf(stderr, "Error depois :%d\n", prev_fdin);
	exe_this(token, env, 0);
	free_env(*env);
	free_list(first_token(token));
	return (exit_status_repository(-1));
}

int	ls_pipe_second(int prev_fdin, int *status, int pid)
{
	if (close(prev_fdin) == -1)
		fprintf(stderr, "Error depois close: %d\n", prev_fdin);
	waitpid(pid, status, 0);
	exit_status_repository(WEXITSTATUS(*status));
	return (exit_status_repository(-1));
}

int	new_minishell(t_token *token, int *fd, int prev_fdin, t_env_list **env)
{
	if ((ft_strncmp(token->text, "./minishell", 12) == 0)
		|| has_redirect_out(token))
	{
		close(fd[1]);
		close(fd[0]);
		if (prev_fdin != 0)
			close(prev_fdin);
		exe_this(token, env, 0);
		free_env(*env);
		free_list(first_token(token));
		return (1);
	}
	return (0);
}

void	command_pipe(int *fd, int prev_fdin, t_token *token, t_env_list **env)
{
	if (close(fd[0]) == -1)
		fprintf(stderr, "Error depois :\n");
	if (prev_fdin != 0)
	{
		if (!has_redirect_in(token))
			dup2(prev_fdin, STDIN_FILENO);
		if (close(prev_fdin) == -1)
			fprintf(stderr, "Error depois :\n");
	}
	dup2(fd[1], STDOUT_FILENO);
	if (close(fd[1]) == -1)
		fprintf(stderr, "Error depois :\n");
	exe_this(token, env, 0);
	free_env(*env);
	free_list(first_token(token));
}

int	next_pipe(int *fd, int prev_fdin, t_token *token, t_env_list **env)
{
	close(fd[1]);
	if (prev_fdin != 0)
	{
		if (close(prev_fdin) == -1)
			fprintf(stderr, "Error depois :%d\n", prev_fdin);
	}
	exe_pipe(next_command(token), env, fd[0]);
	while (waitpid(-1, NULL, WNOHANG) != -1)
		;
	return (exit_status_repository(-1));
}

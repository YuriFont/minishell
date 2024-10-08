/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:36:43 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/28 14:42:56 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirect_out(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == REDIRECT_OUT || temp->token == APPEND)
		{
			if (temp->prev && temp->prev->fd_out != STDOUT_FILENO)
				close_fds(token, 0, 1);
			if (temp->token == REDIRECT_OUT)
				redirection_out(temp);
			else
				redirection_append(temp);
			if (temp->next->fd_out == -1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	error_redirect_in(t_token *temp, int *error)
{
	temp->next->token = NOT_EXIST;
	*error = 1;
	exit_status_repository(1);
	return (1);
}

int	redirect_in(t_token *token)
{
	t_token	*temp;
	int		error;

	temp = token;
	error = 0;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == REDIRECT_IN)
		{
			if (!access(temp->next->text, F_OK | R_OK))
				redirection_in(temp);
			else
				error_redirect_in(temp, &error);
		}
		else if (temp->token == HEREDOC)
		{
			if (init_heredoc(token, temp))
				return (1);
		}
		temp = temp->next;
	}
	if (error)
		return (1);
	return (0);
}

int	print_error_redirectin(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == NOT_EXIST)
		{
			ft_fprintf(2, "minishell: %s: No such file or", temp->text);
			ft_fprintf(2, " directory || Permission denied\n");
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	redirection(t_token *token)
{
	exit_status_repository(0);
	if (redirect_in(token))
	{
		if (exit_status_repository(-1) == 130)
			return (0);
		print_error_redirectin(token);
		close_fds(token, 1, 0);
		return (1);
	}
	if (redirect_out(token))
		return (1);
	return (0);
}

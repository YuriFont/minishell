/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:15:29 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/24 19:13:38 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	reset_fds(t_minishell *mini)
{
	dup2(mini->fd_bk_out, STDOUT_FILENO);
	dup2(mini->fd_bk_in, STDIN_FILENO);
}

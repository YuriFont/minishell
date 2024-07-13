/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:36:43 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/13 17:46:54 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirect_out(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->token != WORD)
		temp = temp->next;
	while (temp && token && token->token != PIPE)
	{
		if (token->token == REDIRECT_OUT || token->token == APPEND)
		{
			if (token->fd_out != STDOUT_FILENO)
				close(temp->fd_out);
			if (token->token == REDIRECT_OUT)
				temp->fd_out = open(token->next->text,
								O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				temp->fd_out = open(token->next->text,
								O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (temp->fd_out == -1)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	redirection(t_token *token)
{
	if (redirect_out(token))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:36:43 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/15 16:21:28 by yufonten         ###   ########.fr       */
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
				redirection_out(temp, token);
			else
				redirection_append(temp, token);
			if (temp->fd_out == -1)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	redirect_in(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->token != WORD)
		temp = temp->next;
	while (token && temp && token->token != PIPE)
	{
		if (token->token == REDIRECT_IN)
		{
			if (!access(token->next->text, F_OK | R_OK))
				redirection_in(temp, token);
			else
			{
				printf("bash: %s: No such file or directory\n",
						token->next->text);
				return (1);
			}
		}
		//else if (token->token == HEREDOC)
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

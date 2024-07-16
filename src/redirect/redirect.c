/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:36:43 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/16 15:13:05 by yufonten         ###   ########.fr       */
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
			if (temp->prev->fd_out != STDOUT_FILENO)
				close_fds(token);
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

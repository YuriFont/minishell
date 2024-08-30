/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:59:16 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/26 20:22:41 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	valid_redirect(t_token *token)
{
	t_token	*temp;
	int		f;

	temp = token;
	f = 0;
	while (temp && f == 0)
	{
		if (temp->next == NULL && (temp->token > 3 && temp->token < 8))
			f = ft_fprintf(2, "mini: syntax error near unexpected token nl'\n");
		else if ((temp->token > 3 && temp->token < 8)
			&& temp->next->token == PIPE)
			f = ft_fprintf(2, "mini: syntax error near unexpected token `|'\n");
		else if ((temp->token > 3 && temp->token < 8) && (temp->next->token > 3
				&& temp->next->token < 8))
			f = ft_fprintf(2, "mini: syntax error near unexpected token `%s'\n",
					token->next->next->text);
		else if ((temp->token == REDIRECT_OUT || temp->token == APPEND)
			&& !access(temp->next->text, F_OK)
			&& access(temp->next->text, W_OK) == -1)
			temp->token = NOT_PERMISSION;
		temp = temp->next;
	}
	if (f != 0)
		return (0);
	return (1);
}

int	valid_pipe(t_token *token)
{
	t_token	*temp;
	int		f;

	temp = token;
	f = 0;
	while (temp && f == 0)
	{
		if (temp->prev == NULL && temp->token == PIPE)
			f = ft_fprintf(2, "mini: syntax error near unexpected token `|'\n");
		else if (temp->next != NULL && temp->token == PIPE
			&& temp->next->token == PIPE)
			f = ft_fprintf(2, "mini: syntax error near unexpected token `|'\n");
		else if (temp->token == PIPE && temp->next == NULL)
			f = ft_fprintf(2, "mini: syntax error, unexpected token command\n");
		temp = temp->next;
	}
	if (f != 0)
		return (0);
	return (1);
}

void	mark_args_of_redirect(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->token != NOT_EXPAND_VA && temp->prev
			&& (temp->prev->token >= 4 && temp->prev->token <= 7)
			&& temp->token != NOT_PERMISSION)
			temp->token = ARGM;
		temp = temp->next;
	}
}

int	check_syntax(t_token *token)
{
	if (!valid_redirect(token))
		return (0);
	if (!valid_pipe(token))
		return (0);
	mark_args_of_redirect(token);
	return (1);
}

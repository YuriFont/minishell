/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:51:50 by erramos           #+#    #+#             */
/*   Updated: 2024/08/24 18:52:46 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirect(t_token *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token->text, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(token->text, "<", 2) == 0)
		return (2);
	else if (ft_strncmp(token->text, "<<", 3) == 0)
		return (3);
	else if (ft_strncmp(token->text, ">>", 3) == 0)
		return (4);
	return (0);
}

int	is_command(t_token *token)
{
	if (token->prev == NULL || (token->prev != NULL
			&& (ft_strncmp(token->prev->text, "|", 2) == 0))
		|| (token->prev != NULL && is_redirect(token->prev->prev)
			&& !is_redirect(token)))
		return (1);
	return (0);
}

int	set_builtin(t_token *token, int has_command)
{
	int	red;

	red = is_redirect(token);
	if (red != 0)
	{
		if (red == 1)
			token->token = REDIRECT_OUT;
		else if (red == 2)
			token->token = REDIRECT_IN;
		else if (red == 3)
			token->token = HEREDOC;
		else
			token->token = APPEND;
	}
	else if (ft_strncmp(token->text, "|", ft_strlen(token->text)) == 0)
		token->token = PIPE;
	else if (is_command(token) && !has_command)
	{
		token->token = COMAND;
		return (1);
	}
	else
		token->token = WORD;
	return (0);
}

void	mark_tokens(t_token *token)
{
	t_token	*temp;
	int		has_command;

	temp = token;
	has_command = 0;
	while (temp)
	{
		if (set_builtin(temp, has_command))
			has_command = 1;
		if (temp->token == PIPE)
			has_command = 0;
		if (temp->prev && temp->prev->token == HEREDOC
			&& (temp->text[0] == '\'' || temp->text[0] == '\"'))
			temp->token = NOT_EXPAND_VA;
		temp = temp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:59:16 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/11 15:59:20 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

int	valid_redirect(t_token *token)
{
	t_token	*temp;
    int     flag;

	temp = token;
    flag = 0;
	while (temp && flag == 0)
	{
		if (temp->token == REDIRECT && temp->next == NULL)
			flag = printf("bash: syntax error near unexpected token `newline'\n");
        if (temp->token == REDIRECT && temp->next->token == PIPE)
            flag = printf("bash: syntax error near unexpected token `|'\n");
        if (temp->token == REDIRECT && temp->next->token == REDIRECT)
            flag = prinf("bash: syntax error near unexpected token `<'\n");
		temp = temp->next;
	}
    if (flag != 0)
    {
        return (0);
    }
	return (1);
}

int valid_pipe(t_token *token)
{
    t_token	*temp;
    int     flag;

	temp = token;
    flag = 0;
	while (temp && flag == 0)
	{
        if (temp->prev == NULL && temp->token == PIPE)
            flag = printf("bash: syntax error near unexpected token `|'\n");
        if (temp->prev == NULL && temp->token == PIPE
            && temp->next->token == PIPE)
            flag = printf("bash: syntax error near unexpected token `||'");
		if (temp->token == PIPE && temp->next->token == PIPE)
			flag = printf("bash: syntax error near unexpected token `|'\n");
        if (temp->token == PIPE && temp->next == NULL)
            flag = prinf("bash: syntax error near unexpected token command\n")
		temp = temp->next;
	}
    if (flag != 0)
    {
        return (0);
    }
	return (1);
}

int check_syntax(t_token *token)
{
    if (!valid_redirect(token))
        return (0);
    if (!valid_pipe(token))
        return (0);
    return (1);
}

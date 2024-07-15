/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:46:55 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/15 16:23:33 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    redirection_in(t_token *temp, t_token *token)
{
    temp->fd_in = open(token->next->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    temp->fd_bk = dup(STDIN_FILENO);
    dup2(temp->fd_out, STDIN_FILENO);
}

void    redirection_out(t_token *temp, t_token *token)
{
    temp->fd_out = open(token->next->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    temp->fd_bk = dup(STDOUT_FILENO);
    dup2(temp->fd_out, STDOUT_FILENO);
}

void    redirection_append(t_token *temp, t_token *token)
{
    temp->fd_out = open(token->next->text, O_WRONLY | O_CREAT | O_APPEND, 0644);
    temp->fd_bk = dup(STDOUT_FILENO);
    dup2(temp->fd_out, STDOUT_FILENO);
}

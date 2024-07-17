/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:46:55 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/16 20:52:47 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    redirection_in(t_token *temp)
{
    temp->next->fd_in = open(temp->next->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    temp->next->fd_bk = dup(STDIN_FILENO);
    dup2(temp->next->fd_out, STDIN_FILENO);
}

void    redirection_out(t_token *temp)
{
    temp->next->fd_out = open(temp->next->text,
            O_WRONLY | O_CREAT | O_TRUNC, 0644);
    temp->next->fd_bk = dup(STDOUT_FILENO);
    dup2(temp->next->fd_out, STDOUT_FILENO);
}

void    redirection_append(t_token *temp)
{
    temp->next->fd_out = open(temp->next->text,
            O_WRONLY | O_CREAT | O_APPEND, 0644);
    temp->next->fd_bk = dup(STDOUT_FILENO);
    dup2(temp->next->fd_out, STDOUT_FILENO);
}

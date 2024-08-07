/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:43:13 by erramos           #+#    #+#             */
/*   Updated: 2024/08/07 18:43:16 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds(t_token *token)
{
	while (token)
	{
		if (token->fd_in != STDIN_FILENO)
		{
			dup2(token->fd_bk, STDIN_FILENO);
			if (close(token->fd_in) == -1)
				fprintf(stderr, "Error close fdin :%d\n", token->fd_bk);
			close(token->fd_bk);
		}
		if (token->fd_out != STDOUT_FILENO)
		{
			dup2(token->fd_bk, STDOUT_FILENO);
			if (close(token->fd_out) == -1)
				fprintf(stderr, "Error close fdout :%d\n", token->fd_bk);
			close(token->fd_bk);
		}
		token = token->next;
	}
	unlink(".heredoc");
}

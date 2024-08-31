/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:26:42 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/28 14:42:32 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_heredoc(int fd_hd, char *input)
{
	close(fd_hd);
	free(input);
	return ;
}

int	init_heredoc(t_token *token, t_token *temp)
{
	close_fds(token, 1, 0);
	heredoc(temp);
	if (exit_status_repository(-1) == 130)
		return (1);
	return (0);
}

int	error_redirectout(t_token *temp)
{
	if (temp->next->fd_out == -1)
	{
		check_exist_or_is_directory(temp->next);
		exit_status_repository(1);
		temp->next->token = NOT_EXIST;
		return (1);
	}
	return (0);
}

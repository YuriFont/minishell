/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:46:55 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/22 10:20:50 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirection_in(t_token *temp)
{
	temp->next->fd_in = open(temp->next->text, O_RDONLY);
	temp->next->fd_bk = dup(STDIN_FILENO);
	dup2(temp->next->fd_in, STDIN_FILENO);
	close(temp->next->fd_in);
}

void	heredoc(t_token *temp)
{
	char	*input;
	int		fd_hd;

	fd_hd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = NULL;
		input = readline("> ");
		if (!input || !ft_strncmp(temp->next->text, input, ft_strlen(input) + 1))
			break ;
		else
		{
			write(fd_hd, input, ft_strlen(input));
			write(fd_hd, "\n", 1);
			free(input);
		}
	}
	if (input)
		free(input);
	close(fd_hd);
	temp->fd_in = open(".heredoc", O_RDONLY);
	temp->fd_bk = dup(STDIN_FILENO);
	dup2(temp->fd_in, STDIN_FILENO);
	close(temp->fd_in);
}

void	redirection_out(t_token *temp)
{
	temp->next->fd_out = open(temp->next->text,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	temp->next->fd_bk = dup(STDOUT_FILENO);
	dup2(temp->next->fd_out, STDOUT_FILENO);
}

void	redirection_append(t_token *temp)
{
	temp->next->fd_out = open(temp->next->text,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	temp->next->fd_bk = dup(STDOUT_FILENO);
	dup2(temp->next->fd_out, STDOUT_FILENO);
}

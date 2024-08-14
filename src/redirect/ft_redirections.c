/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:46:55 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/14 14:47:11 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirection_in(t_token *temp, int in)
{
	temp->next->fd_in = open(temp->next->text, O_RDONLY);
	if (in && temp->prev->prev->token == REDIRECT_IN)
		dup2(temp->prev->fd_bk, STDIN_FILENO);
	temp->next->fd_bk = dup(STDIN_FILENO);
	dup2(temp->next->fd_in, STDIN_FILENO);
}

void	write_in_heredoc(char *input, int fd_hd)
{
	write(fd_hd, input, ft_strlen(input));
	write(fd_hd, "\n", 1);
	free(input);
}

void	heredoc(t_token *temp, int hd)
{
	char	*input;
	int		fd_hd;

	fd_hd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (hd && temp->prev->prev->token == HEREDOC)
		dup2(temp->prev->prev->fd_bk, STDIN_FILENO);
	while (1)
	{
		input = NULL;
		input = readline("> ");
		if (!input || !ft_strncmp(temp->next->text, input,
				ft_strlen(input) + 1))
			break ;
		else
			write_in_heredoc(input, fd_hd);
	}
	if (input)
		free(input);
	if (close(fd_hd) == -1)
		fprintf(stderr, "Error depois : fd_hd\n");
	temp->fd_in = open(".heredoc", O_RDONLY);
	temp->fd_bk = dup(STDIN_FILENO);
	dup2(temp->fd_in, STDIN_FILENO);
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

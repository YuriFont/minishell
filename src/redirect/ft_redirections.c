/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:46:55 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/28 14:18:58 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirection_in(t_token *temp)
{
	close_fds(first_token(temp), 1, 0);
	temp->next->fd_in = open(temp->next->text, O_RDONLY);
	temp->mini->fd_bk_in = dup(STDIN_FILENO);
	dup2(temp->next->fd_in, STDIN_FILENO);
}

void	write_in_heredoc(char *input, int fd_hd, t_token *token)
{
	if (token->token != NOT_EXPAND_VA)
		input = expander_node(input, token->mini->env, 1);
	write(fd_hd, input, ft_strlen(input));
	write(fd_hd, "\n", 1);
	free(input);
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
		if (!input || !ft_strncmp(temp->next->text, input,
				ft_strlen(input) + 1))
			break ;
		if (exit_status_repository(-1) == 130)
			return (exit_heredoc(fd_hd, input));
		else
			write_in_heredoc(input, fd_hd, temp->next);
	}
	if (input)
		free(input);
	if (close(fd_hd) == -1)
		ft_fprintf(2, "Error after : fd_hd\n");
	temp->fd_in = open(".heredoc", O_RDONLY);
	temp->mini->fd_bk_in = dup(STDIN_FILENO);
	dup2(temp->fd_in, STDIN_FILENO);
}

void	redirection_out(t_token *temp)
{
	close_fds(first_token(temp), 0, 1);
	temp->next->fd_out = open(temp->next->text,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	temp->mini->fd_bk_out = dup(STDOUT_FILENO);
	if (error_redirectout(temp))
		return ;
	dup2(temp->next->fd_out, STDOUT_FILENO);
}

void	redirection_append(t_token *temp)
{
	close_fds(first_token(temp), 0, 1);
	temp->next->fd_out = open(temp->next->text,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	temp->mini->fd_bk_out = dup(STDOUT_FILENO);
	if (error_redirectout(temp))
		return ;
	dup2(temp->next->fd_out, STDOUT_FILENO);
}

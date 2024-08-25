/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_utils_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:15:40 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/24 19:15:40 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	file_redirect_valid(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == NOT_EXIST)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	has_redirect_in(t_token *node)
{
	t_token	*temp;

	temp = node;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == REDIRECT_IN || temp->token == HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	print_command_not_found(char *not_found_command)
{
	printf("%s :Command not found\n", not_found_command);
	exit_status_repository(127);
}

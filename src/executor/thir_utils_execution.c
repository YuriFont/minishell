/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thir_utils_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:00:51 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/28 15:25:34 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	reset_for_pipe(t_token *token, t_minishell *mini)
{
	reset_fds(mini);
	redirection(token);
	if (exit_status_repository(-1) == 130)
		return (1);
	return (0);
}

int	has_slash(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	not_found_file(t_token *token)
{
	ft_fprintf(2, "-mini: %s: No such file or directory\n", token->text);
	exit_status_repository(127);
	return (1);
}

int	check_if_exist_and_execute(t_token *token)
{
	struct stat	st;
	char		*aux;

	aux = ft_substr(token->text, 0, ft_strlen(token->text) - 1);
	if (stat(aux, &st) == 0)
	{
		if (!S_ISDIR(st.st_mode))
			ft_fprintf(2, "-mini: %s: Not a directory\n", token->text);
		exit_status_repository(126);
		free(aux);
		return (1);
	}
	free(aux);
	return (0);
}

int	check_exist_or_is_directory(t_token *token)
{
	struct stat	st;

	if (stat(token->text, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_fprintf(2, "-mini: %s: Is a directory\n", token->text);
			exit_status_repository(126);
			return (1);
		}
	}
	else
	{
		if (token->text[ft_strlen(token->text) - 1] == '/')
		{
			if (check_if_exist_and_execute(token))
				return (1);
		}
		not_found_file(token);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:11:06 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/12 14:12:50 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    exe_exit(t_token *token, t_env_list *env)
{
	int		exit_code;

	printf("exit\n");
	free_env(env);
	rl_clear_history();
	exit_code = 0;
	if (!token)
	{
		free_list(token);
		exit(exit_code);
	}
	if (token->next != NULL)
	{
		exit_code = ft_atoi(token->next->text);
		free_list(token);
		exit(exit_code);
	}
	free_list(token);
	exit(exit_code);
}

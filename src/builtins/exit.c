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
    free_list(token);
	free_env(env);
	rl_clear_history();
	exit(0);
}
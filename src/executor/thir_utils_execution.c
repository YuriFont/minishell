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

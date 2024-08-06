/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:35:46 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/13 19:35:46 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exe_pwd(t_token *token)
{
	(void)token;
	ft_putstr_fd(getcwd(NULL, 0), 1);
	ft_putstr_fd("\n", 1);
	exit_status_repository(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+        +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+      +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2024/07/09 09:08:07 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/09 09:08:07 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
			ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		exit_status_repository(130);
	}
}

void	handler_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_if_signal(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			printf("Quit\n");
			exit_status_repository(131);
		}
		else if (WTERMSIG(status) == 2)
		{
			printf("\n");
			exit_status_repository(130);
		}
	}
}

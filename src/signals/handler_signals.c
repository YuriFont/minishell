/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:08:07 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/09 09:08:07 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        write(0, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    handler_signals(void)
{
    struct  sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
       	perror("sigaction");
       	exit(EXIT_FAILURE);
    }
}

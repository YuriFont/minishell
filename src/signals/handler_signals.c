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
        rl_on_new_line();   
        rl_replace_line("", 1);
        rl_redisplay();
    }
    return ;
}

void    handler_signals(void)
{
    struct sigaction    sig;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	sig.sa_handler = signal_handler;
	sigemptyset(&sig.sa_mask);
    sigaddset(&sig.sa_mask, SIGINT);
    sig.sa_flags = 0;
    sigaction(SIGINT, &sig, NULL);
}

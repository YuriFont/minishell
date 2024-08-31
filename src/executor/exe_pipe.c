/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:38:12 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/31 17:38:15 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_pipe(t_minishell *mini)
{
	t_token	*temp;
	int		pid;
	int		status;

	temp = mini->token;
	mini->pipe_fds[0] = dup(STDIN_FILENO);
	mini->pipe_fds[1] = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		status = exe_pipe(temp, &mini->env, 0);
		free_env(mini->env);
		free_list(first_token(temp));
		exit(exit_status_repository(-1));
	}
	else
	{
		waitpid(pid, &status, 0);
		unlink(".heredoc");
		close(mini->pipe_fds[0]);
		close(mini->pipe_fds[1]);
		exit_status_repository(WEXITSTATUS(status));
	}
}

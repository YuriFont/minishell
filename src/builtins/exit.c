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

int	verify_exit_is_numeric(t_token *token)
{
	char	*text;
	int		i;

	i = 0;
	text = token->text;
	if (text[i] == '-' || text[i] == '+')
		i++;
	while (text[i])
	{
		if (!ft_isdigit(text[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exec_exit_is_not_numeric(t_token *token)
{
	printf("minishell: exit: %s: numeric argument required\n",
		token->next->text);
	free_list(token);
	exit(2);
}

void	exec_exit_is_many_arguments(t_token *token)
{
	printf("minishell: exit: too many arguments\n");
	free_list(token);
	exit(1);
}

int	is_overflow(long long exit_code, char *number)
{
	int	mini_nb;

	mini_nb = mini_atoi(number);
	if (mini_nb > 0)
	{
		if (exit_code > mini_nb)
			return (0);
	}
	else if (mini_nb < 0)
	{
		if (mini_nb > exit_code)
			return (0);
	}
	else if (exit_code == 0 && mini_nb == 0)
		return (0);
	return (1);
}

void	exit_with_arguments(t_token *token)
{
	long long	exit_code;

	if (!verify_exit_is_numeric(token->next))
		exec_exit_is_not_numeric(token);
	else if (token->next->next != NULL)
		exec_exit_is_many_arguments(token);
	else
	{
		exit_code = ft_atoll(token->next->text);
		printf("%lld\n", exit_code);
		if (is_overflow(exit_code, token->next->text))
		{
			exec_exit_is_not_numeric(token);
		}
		free_list(token);
		exit(exit_code);
	}
}

void	exe_exit(t_token *token, t_env_list *env, char *prompt, int is_command)
{
	int	exit_code;

	printf("exit\n");
	free_env(env);
	if (prompt != NULL)
		free(prompt);
	rl_clear_history();
	exit_code = exit_status_repository(-1);
	if (is_command && token->next != NULL)
		exit_with_arguments(token);
	free_list(token);
	exit(exit_code);
}

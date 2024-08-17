/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:59 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/08 21:35:37 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	checker_parse(t_minishell *mini)
{
	mark_tokens(mini->token);
	expander_va(mini);
	remove_quotes(mini->token);
	if (!check_syntax(mini->token))
	{
		free_list(mini->token);
		return (1);
	}
	return (0);
}

void	direct_mini(t_minishell *mini)
{
	t_token	*temp;

	temp = mini->token;
	while (temp)
	{
		temp->mini = mini;
		temp = temp->next;
	}
}

int	parse(char *input, char *prompt, t_minishell *mini)
{
	if (!input)
		return (1);
	if (!input[0] || (input[0] && everything_is_space(input)))
	{
		free(prompt);
		free_list(mini->token);
		return (1);
	}
	add_history(input);
	if (!check_input(input))
	{
		free(input);
		free(prompt);
		exit_status_repository(2);
		return (1);
	}
	fill_struct(input, &mini->token);
	direct_mini(mini);
	free(input);
	free(prompt);
	return (checker_parse(mini));
}

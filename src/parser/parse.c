/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:59 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/16 21:58:47 by yufonten         ###   ########.fr       */
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

int	parse(char *input, char *prompt, t_minishell *mini)
{
	if (input[0] == '\0')
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
	free(input);
	free(prompt);
	return (checker_parse(mini));
}

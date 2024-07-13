/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:59 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/13 18:15:08 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	checker_parse(t_token *token)
{
	mark_tokens(token);
	// expander_va(token, env);
	if (!check_syntax(token))
	{
		free_list(token);
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
	if (!check_quotes(input))
	{
		printf("Quotes does not close!\n");
		free(input);
		free(prompt);
		return (1);
	}
	fill_struct(input, &mini->token);
	free(input);
	free(prompt);
	return (checker_parse(mini->token));
}

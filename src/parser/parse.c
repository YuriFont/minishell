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

void	valid_redirect_in(t_token *token)
{
	t_token	*temp;
	t_token	*aux;
	int		remark;

	temp = token;
	aux = NULL;
	remark = 0;
	while (temp)
	{
		if (ft_strlen(temp->text) == 0)
		{
			aux = temp;
			if (temp->prev == NULL && temp->next != NULL)
			{
				temp->mini->token = temp->next;
				temp->next->prev = NULL;
			}
			else
			{

			}
			aux = temp->next;
			temp->next->next->prev = temp;
			temp->next = temp->next->next->next;
			free(aux->next->text);
			free(aux->next);
			free(aux->text);
			free(aux);
			remark = 1;
		}
		temp = temp->next;
	}
	if (remark)
		mark_tokens(token);
}

int	checker_parse(t_minishell *mini)
{
	mark_tokens(mini->token);
	expander_va(mini);
	remove_quotes(mini->token);
	if (!check_syntax(mini->token))
	{
		exit_status_repository(2);
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

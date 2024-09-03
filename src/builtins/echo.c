/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:16:14 by erramos           #+#    #+#             */
/*   Updated: 2024/08/04 18:16:20 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	everything_n(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if (n[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

t_token	*has_next_word(t_token *temp)
{
	temp = temp->next;
	while (temp && temp->token != WORD && temp->token != PIPE)
		temp = temp->next;
	return (temp);
}

void	print_with_echo(t_token *token)
{
	t_token	*aux;

	aux = token;
	if (!aux)
		return ;
	while (ft_strncmp(aux->text, "-n", 2) == 0
		&& everything_n(aux->text + 1))
		aux = aux->next;
	if (aux->token != WORD)
		aux = has_next_word(aux);
	while (aux)
	{
		if (aux && aux->token == PIPE)
			return ;
		if (aux->token == WORD)
			write(1, aux->text, ft_strlen(aux->text));
		aux = has_next_word(aux);
		if (aux && aux->token == WORD && aux->token != PIPE)
			write(1, " ", 1);
	}
}

void	print_echo(t_token *token)
{
	if (token && ft_strncmp(token->text, "-n", 2) == 0
		&& everything_n(token->text + 1))
		print_with_echo(token->next);
	else
	{
		print_with_echo(token);
		write(1, "\n", 1);
	}
	exit_status_repository(0);
}

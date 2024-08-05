/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:23:36 by erramos           #+#    #+#             */
/*   Updated: 2024/08/03 16:23:37 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_amount_redirect(char *input, char redirect)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (input[i] == redirect)
	{
		amount++;
		if (amount > 2)
			return (amount);
		i++;
	}
	return (0);
}

int	check_redirect(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (check_amount_redirect(input + i, input[i]) > 2)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_input(char *input)
{
	if (!check_quotes(input))
	{
		printf("Quotes does not close!\n");
		return (0);
	}
	if (!check_redirect(input))
	{
		printf("syntax error near unexpected token redirect\n");
		return (0);
	}
	return (1);
}

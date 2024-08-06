/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:53:16 by erramos           #+#    #+#             */
/*   Updated: 2024/08/05 16:53:18 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_if_is_quotes(char c, int *single, int *doubleq)
{
	if (c == 39)
	{
		*doubleq = !(*doubleq);
		return (1);
	}
	else if (c == 34)
	{
		*single = !(*single);
		return (1);
	}
	return (0);
}

int	check_if_is_inside_of_quotes(int i, int *double_quotes, int *single_quotes,
		char *input)
{
	char	c;

	c = input[i];
	check_if_is_quotes(c, single_quotes, double_quotes);
	if (input[i] == '\0')
		return (i);
	if (*single_quotes || *double_quotes)
	{
		i = find_next_char(i, c, input);
		if (*single_quotes && input[i] == c)
			*single_quotes = !(*single_quotes);
		else if (*double_quotes && input[i] == c)
			*double_quotes = !(*double_quotes);
	}
	return (i);
}

int	check_quotes(char *input)
{
	int	double_quotes;
	int	single_quotes;
	int	i;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (input[i])
	{
		i = check_if_is_inside_of_quotes(i, &double_quotes, &single_quotes,
				input);
		if (input[i] == '\0')
			break ;
		i++;
	}
	if (double_quotes || single_quotes)
		return (0);
	return (1);
}

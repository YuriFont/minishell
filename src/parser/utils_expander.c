/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:58:30 by erramos           #+#    #+#             */
/*   Updated: 2024/08/05 16:58:32 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	verify_node_expander(char *text)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (text[i])
	{
		if (text[i] == '\"')
			double_quotes = !double_quotes;
		if (text[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		if (!single_quotes && text[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	find_dollar(char *text, int i, int expande_everything)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (text[i])
	{
		if (text[i] == '\"')
			double_quotes = !double_quotes;
		if (text[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		if ((expande_everything || !single_quotes) && text[i] == '$'
			&& (break_point_quotes(text[i + 1])
				&& text[i + 1] != '\'' && text[i + 1] != '\"'))
			return (i);
		i++;
	}
	return (i);
}

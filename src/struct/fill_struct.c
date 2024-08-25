/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:24:57 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/09 08:24:57 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	fill_struct(char *input, t_token **data)
{
	int	i;
	int	start;

	i = 0;
	while (input[i])
	{
		start = i;
		if (input[i] == 34)
			i = add_double_quotes(input, start, data);
		else if (input[i] == 39)
			i = add_sigle_quotes(input, start, data);
		else if (input[i] == '|')
			i = add_pipe(input, start, data);
		else if (input[i] == '>')
			i = add_redirect(input, start, data);
		else if (input[i] == '<')
			i = add_redirect(input, start, data);
		else if (input[i] && input[i] != ' ')
			i = add_word(input, start, data);
		if (!input[i])
			break ;
		i++;
	}
}

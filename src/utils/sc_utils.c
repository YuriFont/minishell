/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:56:38 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/20 09:31:55 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	break_point_quotes(char c)
{
	if (c != ' ' && c != '\0' && c != '|' && c != '>' && c != '<')
		return (1);
	return (0);
}

int	find_last_caracter(char *input, int i)
{
	char	c;

	if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		c = input[i];
	while (input[i] && input[i] == c)
		i++;
	return (i);
}

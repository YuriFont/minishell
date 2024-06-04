/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:40:34 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/26 15:40:34 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	append_node(char *input, t_token **data)
{
	t_token	*node;
	t_token	*last_node;

	if (!data)
		return ;
	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	node->next = NULL;
	node->token = 0;
	node->text = input;
	if (*data == NULL)
	{
		*data = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*data);
		last_node->next = node;
		node->prev = last_node;
	}
}

void	fill_struct(char *input, t_token **data)
{
	char	**split;
	int		i;

	split = ft_split(input, ' ');
	i = 0;
	while (split[i])
	{
		append_node(split[i], data);
		i++;
	}
	free(split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:30:29 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/26 16:30:29 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*find_last_node(t_token *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

/*
	Achar a ultima variavel de ambiente e retornar o no dela
	para adicionar uma nova variavel no nó seguinte
*/

t_env_list	*find_last_node_in_env(t_env_list *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	append_node(char *input, t_token **data)
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
	node->fd_bk = 0;
	node->fd_in = 0;
	node->fd_out = 1;
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

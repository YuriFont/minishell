/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:51:46 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 15:51:46 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    free_list(t_token *list)
{
    t_token *aux;

    while (list != NULL)
    {
        aux = list;
        list = list->next;
        free(aux->text);
        free(aux);
    }
}
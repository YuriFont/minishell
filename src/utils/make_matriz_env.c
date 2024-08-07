/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_matriz_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:20:36 by erramos           #+#    #+#             */
/*   Updated: 2024/08/07 18:20:40 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_variables_in_env(t_env_list *list)
{
	t_env_list	*aux;
	int			count;

	aux = list;
	count = 0;
	while (aux)
	{
		count++;
		aux = aux->next;
	}
	return (count);
}

char	**create_matriz(t_env_list *list, int size_list)
{
	char		**env_clone;
	int			i;
	t_env_list	*aux;

	aux = list;
	i = 0;
	env_clone = (char **)malloc(sizeof(char *) * (size_list + 1));
	while (i < size_list && aux)
	{
		env_clone[i] = ft_strdup(aux->variable);
		i++;
		aux = aux->next;
	}
	env_clone[i] = '\0';
	return (env_clone);
}

char	**env_to_matriz(t_env_list *list)
{
	int			size_list;
	char		**env_clone;

	size_list = count_variables_in_env(list);
	env_clone = create_matriz(list, size_list);
	return (env_clone);
}

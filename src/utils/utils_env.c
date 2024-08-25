/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:58:18 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/14 14:00:03 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*get_envp(void)
{
	extern char		**environ;
	t_env_list		*head;
	t_env_list		*prev;
	t_env_list		*node;
	int				i;

	i = 0;
	head = NULL;
	prev = NULL;
	node = NULL;
	while (environ[i])
	{
		node = malloc(sizeof(t_env_list));
		if (!node)
			return (NULL);
		node->variable = ft_strdup(environ[i]);
		node->next = NULL;
		if (!head)
			head = node;
		else
			prev->next = node;
		prev = node;
		i++;
	}
	return (head);
}

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
	env_clone[i] = NULL;
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

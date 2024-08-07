/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:20:43 by erramos           #+#    #+#             */
/*   Updated: 2024/08/07 18:20:46 by erramos          ###   ########.fr       */
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

void	print_matriz(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
	{
		printf("%s\n", matriz[i]);
		i++;
	}
}

void	free_matriz(char **matriz)
{
	int	i;

	if (!matriz)
		return ;
	i = 0;
	while (matriz[i])
	{
		free(matriz[i]);
		i++;
	}
	free(matriz);
}

int	mini_atoi(char *number)
{
	int		i;
	int		signal;
	int		nb;

	i = 0;
	signal = 0;
	nb = 0;
	if (number[i] == '-' || number[i] == '+')
	{
		if (number[i] == '-')
			signal = 1;
		i++;
	}
	while (number[i] && i < 3)
	{
		nb = nb * 10 + (number[i] - '0');
		i++;
	}
	if (signal)
		nb = nb * -1;
	return (nb);
}

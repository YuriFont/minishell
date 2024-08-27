/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:00:13 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/14 14:00:34 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	exit_status_repository(int exit_status)
{
	static int	status;

	if (0 <= exit_status)
		status = exit_status;
	return (status);
}

char	*get_value_of_exit(void)
{
	int		exit_value;
	char	*exit_code;

	exit_value = exit_status_repository(-42);
	exit_code = ft_itoa(exit_value);
	return (exit_code);
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
		number = number + 1;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_repository.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:20:18 by erramos           #+#    #+#             */
/*   Updated: 2024/08/07 18:20:20 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

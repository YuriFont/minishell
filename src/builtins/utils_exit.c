/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:22:08 by erramos           #+#    #+#             */
/*   Updated: 2024/08/04 18:22:09 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	verify_exit_is_numeric(t_token *token)
{
	char	*text;
	int		i;

	i = 0;
	text = token->text;
	if (text[i] == '-' || text[i] == '+')
		i++;
	while (text[i])
	{
		if (!ft_isdigit(text[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exec_exit_is_not_numeric(t_token *token)
{
	printf("minishell: exit: %s: numeric argument required\n",
		token->next->text);
	free_list(token);
	exit(2);
}

void	exec_exit_is_many_arguments(t_token *token)
{
	printf("minishell: exit: too many arguments\n");
	free_list(token);
	exit(1);
}

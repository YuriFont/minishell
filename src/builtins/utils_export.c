/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:26:08 by erramos           #+#    #+#             */
/*   Updated: 2024/08/04 18:26:09 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	verify_nome_of_variable_is_valid(char *name)
{
	char	*not_valid;
	int		i;
	int		j;

	not_valid = NO_VALID_CHAR;
	i = 0;
	while (name[i])
	{
		j = 0;
		while (not_valid[j])
		{
			if (name[i] == not_valid[j])
			{
				printf("export: `%s': not a valid identifier\n", name);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	change_value_of_env(t_env_list *env, char *variable_change)
{
	char	*temp;

	temp = env->variable;
	env->variable = variable_change;
	free(temp);
}

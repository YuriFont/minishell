/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:26:08 by erramos           #+#    #+#             */
/*   Updated: 2024/08/26 20:18:00 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_not_valid_export(char *name)
{
	ft_fprintf(2, "export: `%s': not a valid identifier\n", name);
	exit_status_repository(1);
	return (0);
}

int	verify_nome_of_variable_is_valid(char *name)
{
	char	*not_valid;
	int		i;
	int		j;

	not_valid = NO_VALID_CHAR;
	i = 0;
	if (ft_isdigit(name[0]))
		return (error_not_valid_export(name));
	while (name[i])
	{
		j = 0;
		while (not_valid[j])
		{
			if (name[i] == not_valid[j])
				return (error_not_valid_export(name));
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

void	add_env(t_env_list *env, t_token *temp)
{
	char	*name;
	char	*value;
	int		is_free;

	is_free = 0;
	name = valid_new_variable(temp->text);
	if (!name)
		return ;
	if (verify_exist_in_env(name, env, temp))
		return ;
	value = ft_strchr(temp->text, '=');
	if (value)
		value = value + 1;
	else
	{
		value = ft_strdup("");
		is_free = 1;
	}
	add_new_variable(env, name, value, is_free);
	free(name);
}

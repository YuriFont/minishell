/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:16:26 by erramos           #+#    #+#             */
/*   Updated: 2024/08/04 18:16:33 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env_list(t_env_list *list)
{
	t_env_list	*aux;

	aux = list;
	while (aux)
	{
		printf("%s\n", aux->variable);
		aux = aux->next;
	}
	exit_status_repository(0);
}

t_env_list	*get_in_env(char *search, t_env_list *list)
{
	t_env_list	*aux;

	aux = list;
	while (aux)
	{
		if (!ft_strncmp(search, aux->variable, ft_strlen(search)))
		{
			if (aux->variable[ft_strlen(search)] == '=')
				return (aux);
		}
		aux = aux->next;
	}
	return (NULL);
}

char	*get_value_in_variable(char *variable, t_env_list *list)
{
	char		*value;
	t_env_list	*aux;

	aux = get_in_env(variable, list);
	if (!aux)
		return (NULL);
	value = ft_strchr(aux->variable, '=');
	if (!value)
		return (NULL);
	return (value + 1);
}

char	*change_value_of_variable(char *new_value, char *variable)
{
	char	*name;
	char	*new_variable;
	char	*result;

	name = ft_strrchr(variable, '=');
	if (name)
	{
		result = ft_substr(variable, 0, ft_strlen(variable) - ft_strlen(name));
		new_variable = ft_strjoinf(result, "=");
	}
	else
	{
		result = variable;
		new_variable = ft_strjoin(result, "=");
	}
	new_variable = ft_strjoinf(new_variable, new_value);
	return (new_variable);
}

void	add_new_variable(t_env_list *env, char *variable,
		char *value, int is_free)
{
	t_env_list	*aux;
	t_env_list	*new_node;
	char		*new_variable;

	new_variable = change_value_of_variable(value, variable);
	aux = find_last_node_in_env(env);
	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		return ;
	new_node->variable = new_variable;
	new_node->next = NULL;
	aux->next = new_node;
	if (is_free)
		free(value);
}

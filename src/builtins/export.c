/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:16:41 by erramos           #+#    #+#             */
/*   Updated: 2024/08/04 18:16:43 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_name_of_variable(char *variable)
{
	char	*find_equal;
	char	*name_variable;

	find_equal = ft_strchr(variable, '=');
	if (!find_equal)
		return (ft_strdup(variable));
	name_variable = ft_substr(variable, 0,
			ft_strlen(variable) - ft_strlen(find_equal));
	return (name_variable);
}

/*
	Valida apenas o nome da "variavel de ambiente"
*/

char	*valid_new_variable(char *new_variable)
{
	char	*name_variable;

	name_variable = get_name_of_variable(new_variable);
	if (!name_variable || ft_strlen(name_variable) == 0)
	{
		if (!verify_nome_of_variable_is_valid(new_variable))
		{
			free(name_variable);
			return (NULL);
		}
		return (new_variable);
	}
	if (!verify_nome_of_variable_is_valid(name_variable))
	{
		free(name_variable);
		return (NULL);
	}
	return (name_variable);
}

int	verify_exist_in_env(char *name, t_env_list *env, t_token *token)
{
	t_env_list	*result;
	char		*value;
	char		*value_change;

	result = get_in_env(name, env);
	if (!result)
		return (0);
	value = ft_strchr(token->text, '=');
	if (value)
		value = value + 1;
	else
		return (1);
	value_change = change_value_of_variable(value, name);
	change_value_of_env(result, value_change);
	free(name);
	return (1);
}

void	print_export(t_env_list *env)
{
	t_env_list	*temp;
	char		*print_variable;
	char		*name;

	temp = env;
	while (temp)
	{
		name = get_name_of_variable(temp->variable);
		print_variable = ft_strdup("declare -x ");
		print_variable = ft_strjoinf(print_variable, name);
		print_variable = ft_strjoinf(print_variable, "=\"");
		print_variable = ft_strjoinf(print_variable,
				get_value_in_variable(name, env));
		print_variable = ft_strjoinf(print_variable, "\"");
		printf("%s\n", print_variable);
		free(print_variable);
		free(name);
		temp = temp->next;
	}
	exit_status_repository(0);
}

/*
	Inserir uma nova "variavel de ambiente" ao 
	digitar export + <nome da variavel=conteudo da variavel>,
	necessario verificar se a variavel ja existe
	 e alterar apenas o valor ao invez de mallocar.
*/

void	insert_in_env(t_env_list *env, t_token *token)
{
	char	*name;
	char	*value;
	int		is_free;

	exit_status_repository(0);
	is_free = 0;
	if (!token || (token && token->token == PIPE))
		return (print_export(env));
	name = valid_new_variable(token->text);
	if (!name)
		return ;
	if (verify_exist_in_env(name, env, token))
		return ;
	value = ft_strchr(token->text, '=');
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

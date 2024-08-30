/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:16:51 by erramos           #+#    #+#             */
/*   Updated: 2024/08/04 18:16:54 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Procura a variavel de ambiente na env_list
	 e a remove, tem mais de 25 linhas :(
*/

int	is_end_of_variable(char *variable, t_env_list *node)
{
	char	*end;

	if (ft_strlen(variable) > ft_strlen(node->variable))
		return (0);
	end = node->variable + ft_strlen(variable);
	if (end[0] == '=')
		return (1);
	return (0);
}

int	is_this_node(t_env_list *temp, char *variable)
{
	if (ft_strncmp(temp->variable, variable,
			ft_strlen(variable)) == 0)
	{
		if (is_end_of_variable(variable, temp))
			return (1);
	}
	return (0);
}

void	remove_env(t_token *node, t_env_list **env)
{
	t_env_list	*temp;
	t_env_list	*prev;
	char		*variable;

	variable = node->text;
	temp = *env;
	prev = NULL;
	while (temp)
	{
		if (is_this_node(temp, variable))
			break ;
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	if (!prev)
		*env = (*env)->next;
	else
		prev->next = temp->next;
	free(temp->variable);
	free(temp);
}

void	remove_variable_env(t_token *node, t_env_list **env)
{
	t_token	*temp;

	exit_status_repository(0);
	if (!node)
		return ;
	temp = node;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == WORD)
			remove_env(temp, env);
		temp = temp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:09:33 by erramos           #+#    #+#             */
/*   Updated: 2024/08/03 16:10:28 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_of_args(t_token *list)
{
	int		i;
	t_token	*aux;

	i = 0;
	aux = list;
	while (aux && aux->token != PIPE)
	{
		if (aux->token == WORD)
			i++;
		aux = aux->next;
	}
	return (i);
}

char	**elaborating_args(t_token *token, char *command)
{
	t_token	*aux;
	int		count_args;
	int		i;
	char	**args;

	i = 2;
	aux = token;
	count_args = count_of_args(token);
	args = (char **)malloc(sizeof(char *) * (count_args + 3));
	args[0] = ft_strdup(command);
	args[1] = ft_strdup("--color=auto");
	while (aux && aux->token != PIPE)
	{
		if (aux->token == WORD)
			args[i++] = ft_strdup(aux->text);
		aux = aux->next;
	}
	args[i] = NULL;
	return (args);
}

char	**create_args_options(char *command, t_token *token)
{
	char	**args;
	int		count_args;
	int		i;
	t_token	*aux;

	i = 1;
	aux = token;
	count_args = count_of_args(token);
	if (ft_strncmp(command, "ls", 3) == 0)
		args = elaborating_args(token, command);
	else
	{
		args = (char **)malloc(sizeof(char *) * (count_args + 2));
		args[0] = ft_strdup(command);
		while (aux && aux->token != PIPE)
		{
			if (aux->token == WORD)
				args[i++] = ft_strdup(aux->text);
			aux = aux->next;
		}
		args[i] = NULL;
	}
	return (args);
}

char	**create_args(char *command, t_token *token)
{
	char	**args;

	if (!token)
	{
		args = (char **)malloc(sizeof(char *) * 3);
		args[0] = ft_strdup(command);
		if (ft_strncmp(command, "ls", 3) == 0)
		{
			args[1] = ft_strdup("--color=auto");
			args[2] = NULL;
		}
		else
			args[1] = NULL;
	}
	else
		args = create_args_options(command, token);
	return (args);
}

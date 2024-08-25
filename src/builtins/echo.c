/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:16:14 by erramos           #+#    #+#             */
/*   Updated: 2024/08/04 18:16:20 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Se der sum um echo sem argumentos e printado apenas
	uma quebra de linha
*/

void	print_with_echo(t_token *token)
{
	t_token	*aux;

	aux = token;
	if (!aux)
		return ;
	while (ft_strncmp(aux->text, "-n", 3) == 0)
		aux = aux->next;
	while (aux)
	{
		if (aux && aux->token == PIPE)
			return ;
		if (aux->token == WORD)
			write(1, aux->text, ft_strlen(aux->text));
		aux = aux->next;
		if (aux && aux->token == WORD)
			write(1, " ", 1);
	}
}

/*
	Não sei como funciona, existe a possibilidade do texto
	entrar entre aspas no echo, todo o espaco que estiver
	entre as aspas não e alterado, no caso deveria printar
	os espaços tambem, porem a split retirar os espaço e
	divide o que esta ente aspas
*/

void	print_echo(t_token *token)
{
	if (token && ft_strncmp(token->text, "-n", 3) == 0)
		print_with_echo(token->next);
	else
	{
		print_with_echo(token);
		write(1, "\n", 1);
	}
	exit_status_repository(0);
}

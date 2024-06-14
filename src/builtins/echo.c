#include "../../inc/minishell.h"

void	print_with_echo(t_token *token)
{
	t_token	*aux;

	aux = token;
	if (!aux)
		return ;
	while (aux)
	{
		write(1, aux->text, ft_strlen(aux->text));
		aux = aux->next;
		if (aux)
			write(1, " ", 1);
	}
}

void	print_echo(t_token *token)
{
	if (token && ft_strncmp(token->text, "-n", 2) == 0)
		print_with_echo(token->next);
	else
	{
		print_with_echo(token);
		write(1, "\n", 1);
	}
}

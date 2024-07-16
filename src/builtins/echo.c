#include "../../inc/minishell.h"

/*
	Se der sum um echo sem argumentos e printado apenas
	uma quebra de linha
*/

void	print_with_echo(t_token *token, int fd_out)
{
	t_token	*aux;

	aux = token;

	if (!aux)
		return ;
	while (ft_strncmp(aux->text, "-n", 3) == 0)
		aux = aux->next;
	while (aux)
	{
		if (aux->token == PIPE || (aux->token > 3 && aux->token < 8))
			return ;
		write(fd_out, aux->text, ft_strlen(aux->text));
		aux = aux->next;
		if (aux)
			write(fd_out, " ", 1);
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
	int	fd_out;

	fd_out = get_fd(token);
	if (token && ft_strncmp(token->text, "-n", 3) == 0)
		print_with_echo(token->next, fd_out);
	else
	{
		print_with_echo(token, fd_out);
		write(fd_out, "\n", 1);
	}
}

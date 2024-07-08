#include "../../inc/minishell.h"

int	is_redirect(char *text)
{
	if (ft_strncmp(text, ">", ft_strlen(text)) == 0)
		return (1);
	else if (ft_strncmp(text, "<", ft_strlen(text)) == 0)
		return (1);
	else if (ft_strncmp(text, "<<", ft_strlen(text)) == 0)
		return (1);
	else if (ft_strncmp(text, ">>", ft_strlen(text)) == 0)
		return (1);
	return (0);
}

int	is_command(t_token *token)
{
	if (token->prev == NULL || (token->prev != NULL
			&& (ft_strncmp(token->prev->text, "|",
					ft_strlen(token->prev->text)) == 0)
			&& !is_redirect(token->text)))
		return (1);
	return (0);
}

void	set_builtin(t_token *token)
{
	if (is_command(token))
		token->token = COMAND;
	else if (ft_strncmp(token->text, "|", ft_strlen(token->text)) == 0)
		token->token = PIPE;
	else if (is_redirect(token->text))
		token->token = REDIRECT;
	else
		token->token = WORD;
}

void	mark_tokens(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		set_builtin(temp);
		printf("%s %d\n", temp->text, temp->token);
		temp = temp->next;
	}
}

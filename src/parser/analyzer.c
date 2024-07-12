#include "../../inc/minishell.h"

int	is_redirect(char *text)
{
	if (ft_strncmp(text, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(text, "<", 2) == 0)
		return (2);
	else if (ft_strncmp(text, "<<", 3) == 0)
		return (3);
	else if (ft_strncmp(text, ">>", 3) == 0)
		return (4);
	return (0);
}

int	is_command(t_token *token)
{
	if (token->prev == NULL || (token->prev != NULL
			&& (ft_strncmp(token->prev->text, "|", 2) == 0)
			&& !is_redirect(token->text)))
		return (1);
	return (0);
}

void	set_builtin(t_token *token)
{
	int	red;

	red = is_redirect(token->text);
	if (red != 0)
	{
		if (red == 1)
			token->token = REDIRECT_OUT;
		else if (red == 2)
			token->token = REDIRECT_IN;
		else if (red == 3)
			token->token = HEREDOC;
		else
			token->token = APPEND;
	}
	else if (ft_strncmp(token->text, "|", ft_strlen(token->text)) == 0)
		token->token = PIPE;
	else if (is_command(token))
		token->token = COMAND;
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

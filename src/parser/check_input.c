#include "../../inc/minishell.h"

int	check_if_is_quotes(char c, int *single, int *doubleq)
{
	if (c == 39)
	{
		*doubleq = !(*doubleq);
		return (1);
	}
	else if (c == 34)
	{
		*single = !(*single);
		return (1);
	}
	return (0);
}

int	check_quotes(char *input)
{
	int		double_quotes;
	int		single_quotes;
	int		i;
	char	c;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (input[i])
	{
		c = input[i];
		check_if_is_quotes(c, &single_quotes, &double_quotes);
		if (input[i] == '\0')
			break ;
		if (single_quotes || double_quotes)
		{
			i = find_next_char(i, c, input);
			if (single_quotes && input[i] == c)
				single_quotes = !single_quotes;
			else if (double_quotes && input[i] == c)
				double_quotes = !double_quotes;
		}
		i++;
	}
	if (double_quotes || single_quotes)
		return (0);
	return (1);
}

int	check_amount_redirect(char *input, char redirect)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (input[i] == redirect)
	{
		amount++;
		if (amount > 2)
			return (amount);
		i++;
	}
	return (0);
}

int	check_redirect(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (check_amount_redirect(input + i, input[i]) > 2)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_input(char *input)
{
	if (!check_quotes(input))
	{
		printf("Quotes does not close!\n");
		return (0);
	}
	if (!check_redirect(input))
	{
		printf("syntax error near unexpected token redirect\n");
		return (0);
	}
	return (1);
}

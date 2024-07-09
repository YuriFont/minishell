#include "../../inc/minishell.h"

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
		if (input[i] == 39)
		{
			c = input[i];
			double_quotes = !double_quotes;
		}
		if (input[i] == 34)
		{
			c = input[i];
			single_quotes = !single_quotes;
		}
		if (single_quotes || double_quotes)
		{
			i++;
			while (input[i] && input[i] != c)
				i++;
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
		if (input[i] == '\'' || input[i] == '\"')
			i = find_next_char(i, input[i], input);
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

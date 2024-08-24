/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:32:20 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/13 20:32:20 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	find_quotes(char *text)
{
	int		i;
	char	c;

	i = 0;
	while (text[i])
	{
		c = text[i];
		if (c == '\'' || c == '"')
		{
			text[i] = -10;
			i = find_next_char(i, c, text);
			if (text[i] == '\'' || text[i] == '"')
				text[i] = -10;
		}
		if (!text[i])
			break ;
		i++;
	}
}

int	count_char_without_quotes(char *text)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (text[i])
	{
		if (text[i] != -10)
			count++;
		i++;
	}
	return (count);
}

char	*copy_new_text(char *text, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (text[i])
	{
		if (text[i] != -10)
		{
			new[j] = text[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*new_text_without_quotes(char *text)
{
	char	*new;
	int		amount_char;

	amount_char = count_char_without_quotes(text);
	new = malloc(sizeof(char) * amount_char + 1);
	if (!new)
		return (NULL);
	new = copy_new_text(text, new);
	free(text);
	return (new);
}

void	remove_quotes(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		printf("%s %d\n", temp->text, temp->token);
		find_quotes(temp->text);
		temp->text = new_text_without_quotes(temp->text);
		temp = temp->next;
	}
}

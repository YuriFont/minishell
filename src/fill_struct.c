/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/26 15:40:34 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/26 15:40:34 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	append_node(char *input, t_token **data)
{
	t_token *node;
	t_token *last_node;

	if (!data)
		return ;
	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	node->next = NULL;
	node->token = 0;
	node->text = input;
	if (*data == NULL)
	{
		*data = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*data);
		last_node->next = node;
		node->prev = last_node;
	}
}

// void	fill_struct(char *input, t_token **data)
// {
// 	char **split;
// 	int i;

// 	split = ft_split(input, ' ');
// 	i = 0;
// 	while (split[i])
// 	{
// 		append_node(split[i], data);
// 		i++;
// 	}
// 	free(split);
// }

int	double_quotes(char *input, int start, t_token **data)
{
	int		i;
	char	*str;

	i = start + 1;
	while (input[i])
	{
		if (input[i] == 34 && (input[i + 1] != ' ' || input[i + 1] != '\0'))
		{
			i++;
			continue ;
		}
		else if (input[i] == 34 && (input[i + 1] == ' ' || input[i + 1] == '\0'))
			break ;
		i++;
	}
	// if (!input[i])
	// 	return (i);
	str = ft_substr(input, start, i - start + 1);
	append_node(str, data);
	return (i);
}

int	sigle_quotes(char *input, int start, t_token **data)
{
	int		i;
	char	*str;

	i = start + 1;
	while (input[i])
	{
		if (input[i] == 39 && (input[i + 1] != ' ' || input[i + 1] != '\0'))
		{
			i++;
			continue ;
		}
		else if (input[i] == 39 && (input[i + 1] == ' ' || input[i + 1] == '\0'))
			break ;
		i++;
	}
	str = ft_substr(input, start, i - start + 1);
	append_node(str, data);
	return (i);
}

int	add_word(char *input, int start, t_token **data)
{
	int		i;
	char	*str;

	i = start + 1;
	while (input[i] && input[i] != ' ')
	{
		if (input[i] == 34 || input[i] == 39)
			break ;
		i++;
	}
	str = ft_substr(input, start, i - start);
	append_node(str, data);
	if (input[i] == 34 || input[i] == 39)
		i--;
	return (i);
}

void	fill_struct(char *input, t_token **data)
{
	int	i;
	int	start;

	i = 0;
	while (input[i])
	{
		start = i;
		if (input[i] == 34)
			i = double_quotes(input, start, data);
		else if (input[i] == 39)
			i = sigle_quotes(input, start, data);
		else if (input[i] && input[i] != ' ')
			i = add_word(input, start, data);
		if (!input[i])
			break ;
		i++;
	}
}

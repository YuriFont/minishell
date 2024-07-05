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
	int		is_letter;
	char	*str;

	i = start + 1;
	is_letter = 0;
	while (input[i])
	{
		if (input[i] == 34 && (input[i + 1] != ' ' && input[i + 1] != '\0' && input[i + 1] != '|'))
		{
			i++;
			is_letter = 1;
			continue ;
		}
		else if ((input[i] == 34
			&& (input[i + 1] == ' ' || input[i + 1] == '\0'))
				|| (is_letter && input[i + 1] == ' ') || input[i + 1] == '|')
			break ;
		i++;
	}
	str = ft_substr(input, start, i - start + 1);
	append_node(str, data);
	return (i);
}

int	sigle_quotes(char *input, int start, t_token **data)
{
	int		i;
	int		is_letter;
	char	*str;

	i = start + 1;
	is_letter = 0;
	while (input[i])
	{
		if (input[i] == 39 && (input[i + 1] != ' ' && input[i + 1] != '\0' && input[i + 1] != '|'))
		{
			i++;
			is_letter = 0;
			continue ;
		}
		else if ((input[i] == 39
			&& (input[i + 1] == ' ' || input[i + 1] == '\0'))
				|| (is_letter && input[i + 1] == ' ') || input[i + 1] == '|')
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
		if (input[i] == '|'
			|| input[i] == '>' || input[i] == '<')
			break ;
		i++;
	}
	str = ft_substr(input, start, i - start);
	append_node(str, data);
	// printf("%s\n", input+i);
	if ((input[i] == 34 || input[i] == 39
		|| input[i] == '|' || input[i] == '>'
			|| input[i] == '<') && (ft_strncmp(input + i, ">>", 2) || ft_strncmp(input + i, "<<", 2)))
		i--;
	return (i);
}

int	add_pipe(char *input, int start, t_token **data)
{
	int		i;
	char	*str;
	
	i = start + 1;
	str = ft_substr(input, start, i - start);
	append_node(str, data);
	return (start);
}

int	add_redirect(char *input, int start, t_token **data)
{
	int		i;
	char	*str;
	char	c;
	
	i = start;
	c = input[i];
	while (input[i] == c)
		i++;
	str = ft_substr(input, start, i - start);
	append_node(str, data);
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
		else if (input[i] == '|')
			i = add_pipe(input, start, data);
		else if (input[i] == '>')
			i = add_redirect(input, start, data);
		else if (input[i] == '<')
			i = add_redirect(input, start, data);
		else if (input[i] && input[i] != ' ')
			i = add_word(input, start, data);
		if (!input[i])
			break ;
		i++;
	}
}

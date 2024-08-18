/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_input_separator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:04:25 by erramos           #+#    #+#             */
/*   Updated: 2024/08/18 18:34:35 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_double_quotes(char *input, int start, t_token **data)
{
	int		i;
	char	*str;

	i = start;
	while (input[i])
	{
		i = find_next_char(i, 34, input);
		if (input[i] == 34 && (break_point_quotes(input[i + 1])))
		{
			while (input[i] && break_point_quotes(input[i + 1]))
			{
				i++;
				if (input[i] == 34)
					i = find_next_char(i, 34, input);
			}
		}
		if ((input[i] && !break_point_quotes(input[i + 1])) || !input[i])
			break ;
		i++;
	}
	if (data == NULL)
		return (i);
	str = ft_substr(input, start, i - start + 1);
	append_node(str, data);
	return (i);
}

int	add_sigle_quotes(char *input, int start, t_token **data)
{
	int		i;
	char	*str;

	i = start;
	while (input[i])
	{
		i = find_next_char(i, 39, input);
		if (input[i] == 39 && (break_point_quotes(input[i + 1])))
		{
			while (input[i] && break_point_quotes(input[i + 1]))
			{
				i++;
				if (input[i] == 39)
					i = find_next_char(i, 39, input);
			}
			if (input[i] == 34)
				i = add_double_quotes(input, i, NULL);
		}
		if (!break_point_quotes(input[i + 1]))
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
		if (input[i] == 34)
			i = find_next_char(i, 34, input);
		else if (input[i] == 39)
			i = find_next_char(i, 39, input);
		if (input[i] == '|' || input[i] == '>' || input[i] == '<' || !input[i])
			break ;
		i++;
	}
	str = ft_substr(input, start, i - start);
	append_node(str, data);
	if ((input[i] == 34 || input[i] == 39 || input[i] == '|' || input[i] == '>'
			|| input[i] == '<') && (ft_strncmp(input + i, ">>", 2)
			|| ft_strncmp(input + i, "<<", 2)))
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

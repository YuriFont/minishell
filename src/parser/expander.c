/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/13 20:12:14 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/13 20:12:14 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	verify_node_expander(char *text)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (text[i])
	{
		if (text[i] == '\"')
			double_quotes = !double_quotes;
		if (text[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		if (!single_quotes && text[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	find_dollar(char *text, int i)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (text[i])
	{
		if (text[i] == '\"')
			double_quotes = !double_quotes;
		if (text[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		if (!single_quotes && text[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*get_variable(char *text, int i, t_env_list *env)
{
	int		start;
	char	*variable;
	char	*content_variable;

	start = i + 1;
	i++;
	while (break_point_quotes(text[i + 1]) && (text[i + 1] != '\''
			&& text[i + 1] != '\"' && text[i + 1] != '$'))
		i++;
	variable = ft_substr(text, start, i - start + 1);
	if (ft_strncmp(variable, "?", 1) == 0)
	{
		free(variable);
		content_variable = get_value_of_exit();
		return (content_variable);
	}
	content_variable = get_value_in_variable(variable, env);
	free(variable);
	if (!content_variable)
		return (ft_strdup(""));
	return (ft_strdup(content_variable));
}

char	*get_prev_content(char *result, char *text, int *i)
{
	char	*prev;
	int		prev_i;

	prev_i = *i;
	*i = find_dollar(text, *i);
	prev = ft_substr(text, prev_i, *i - prev_i);
	result = ft_strjoinf(result, prev);
	free(prev);
	return (result);
}

int	get_next_content_after_expander(char *text, int *i)
{
	if (text[*i + 1] != '\0' && text[*i] == '$' && text[*i + 1] == '?')
	{
		*i += 2;
		return (0);
	}
	else
	{
		while (break_point_quotes(text[*i + 1]) && text[*i + 1] != '\''
			&& text[*i + 1] != '\"' && text[*i + 1] != '$')
			*i += 1;
	}
	return (1);
}

char	*expander_node(char *text, t_env_list *env)
{
	char	*result;
	char	*expansor;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (text[i])
	{
		result = get_prev_content(result, text, &i);
		if (text[i] == '\0')
			break ;
		expansor = get_variable(text, i, env);
		result = ft_strjoinf(result, expansor);
		free(expansor);
		if (!get_next_content_after_expander(text, &i))
			continue ;
		i++;
	}
	free(text);
	return (result);
}

void	expander_va(t_minishell *mini)
{
	t_token	*node;

	node = mini->token;
	while (node)
	{
		if (verify_node_expander(node->text))
			node->text = expander_node(node->text, mini->env);
		node = node->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:18:08 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/26 17:20:19 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*create_prompt(void)
{
	char	*prompt;
	char	*host;
	char	*name;
	char	*dir;

	host = getenv("LOGNAME");
	name = getenv("NAME");
	dir = getenv("PWD") + (6 + ft_strlen(host));
	prompt = ft_strjoin("\e[0;32m", host);
	prompt = ft_strjoinf(prompt, "@");
	prompt = ft_strjoinf(prompt, name);
	prompt = ft_strjoinf(prompt, "\e[0m");
	prompt = ft_strjoinf(prompt, ":");
	prompt = ft_strjoinf(prompt, "\e[0;34m");
	prompt = ft_strjoinf(prompt, "~");
	prompt = ft_strjoinf(prompt, dir);
	prompt = ft_strjoinf(prompt, "\e[0m");
	prompt = ft_strjoinf(prompt, "$ ");
	return (prompt);
}

int main(void)
{
	char	*prompt;
	char	*input;
	t_token	*data;

	data = NULL;
	while (1)
	{
		prompt = create_prompt();
		input = readline(prompt);
		add_history(input);
		fill_struct(input, &data);
		while (data != NULL)
		{
			printf("%s\n", data->text);
			data = data->next;
		}
		free(input);
		free(prompt);
    }
	return (0);
}

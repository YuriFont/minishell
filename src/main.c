/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:18:08 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 14:18:08 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*create_prompt(char *host, char *name, char *dir)
{
	char	*prompt;

	prompt = ft_strjoin(host, "@");
	prompt = ft_strjoinf(prompt, name);
	prompt = ft_strjoinf(prompt, ":~");
	prompt = ft_strjoinf(prompt, dir);
	prompt = ft_strjoinf(prompt, "$ ");
	return (prompt);
}

int main(void)
{
    char	*name;
    char	*user;
    char	*dir;
	char	*prompt;
	char	*input;

    while (1)
    {
		host = getenv("LOGNAME");
		name = getenv("NAME");
		dir = getenv("PWD");
		dir += (6 + ft_strlen(name));
		prompt = create_prompt(host, name, dir);
		input = readline(prompt);
		add_history(input);
		free(input);
		free(prompt);
    }
	return (0);
}

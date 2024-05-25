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

char	*create_prompt(char *name, char *user, char *dir)
{
	char *prompt;

	prompt = ft_strjoin(name, "@");
	prompt = ft_strjoinf(prompt, user);
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
		name = getenv("NAME");
    	user = getenv("LOGNAME");
    	dir = getenv("PWD");
		dir += (6 + ft_strlen(name));
		prompt = create_prompt(name, user, dir);
        input = readline(prompt);
		add_history(input);
		free(input);
		free(prompt);
    }
    return (0);
}
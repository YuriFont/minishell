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

	host = getenv("HOSTNAME");
	name = getenv("USER");
	dir = getenv("PWD") + (ft_strlen(name));
	prompt = ft_strjoin("\e[0;32m", name);
	prompt = ft_strjoinf(prompt, "@");
	prompt = ft_strjoinf(prompt, host);
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
	t_env_list *env;

	env = NULL;
	data = NULL;
	env = get_envp();
//	print_env_list(env);
	char *resultado = get_in_env("USER",env);
	printf("%s", resultado);
	while (1)
	{
		prompt = create_prompt();
		input = readline(prompt);
		if (input[0])
		{
			add_history(input);
			fill_struct(input, &data);
			check_builtins(data);
			free_list(data);
			data = NULL;
		}
		free(input);
		free(prompt);
    }
	free_env(env);
	return (0);
}

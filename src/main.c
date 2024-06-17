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

static char	*organize_prompt(char *host, char *name, char *dir)
{
	char	*prompt;

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

static char	*create_prompt(t_env_list *env)
{
	char	*prompt;
	char	*host;
	char	*name;
	char	*dir;
	char	*name_dir;

	host = get_value_in_variable("LOGNAME", env);
	name = get_value_in_variable("NAME", env);
	name_dir = getcwd(NULL, 0);
	dir = ft_strnstr(name_dir, host, ft_strlen(name_dir));
	if (dir)
		dir = dir + ft_strlen(host);
	else
		dir = name_dir;
	prompt = organize_prompt(host, name, dir);
	free(name_dir);
	return (prompt);
}

int	main(void)
{
	char		*prompt;
	char		*input;
	t_minishell	mini;
	// char		**matriz;

	mini.token = NULL;
	mini.env = get_envp();
	while (1)
	{
		prompt = create_prompt(mini.env);
		input = readline(prompt);
		if (input[0])
		{
			add_history(input);
			fill_struct(input, &mini.token);
			check_commands(mini.token, mini.env);
			free_list(mini.token);
			mini.token = NULL;
			// matriz = env_to_matriz(mini.env);
			// print_matriz(matriz);
			// free_matriz(matriz);
		}
		free(input);
		free(prompt);
	}
	free_env(mini.env);
	return (0);
}

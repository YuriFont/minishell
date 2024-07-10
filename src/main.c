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

	prompt = ft_strjoin(GREEN, name);
	prompt = ft_strjoinf(prompt, "@");
	prompt = ft_strjoinf(prompt, host);
	prompt = ft_strjoinf(prompt, RESET_COLOR);
	prompt = ft_strjoinf(prompt, ":");
	prompt = ft_strjoinf(prompt, BLUE);
	prompt = ft_strjoinf(prompt, "~");
	prompt = ft_strjoinf(prompt, dir);
	prompt = ft_strjoinf(prompt, RESET_COLOR);
	prompt = ft_strjoinf(prompt, "$ ");
	return (prompt);
}

char	*get_local_of_session(char *host)
{
	char *temp;
	int	i;

	i = 0;
	temp = ft_strchr(host, '/') + 1;
	while (temp[i])
	{
		if (temp[i] == '.')
		{
			temp[i] = '\0';
			break ;
		}
		i++;
	}
	return (temp);
}

static char	*create_prompt(t_env_list *env)
{
	char	*prompt;
	char	*host;
	char	*name;
	char	*dir;
	char	*name_dir;

	host = get_value_in_variable("SESSION_MANAGER", env);
	if (host)
		host = get_local_of_session(host);
	else
		host = get_value_in_variable("LOGNAME", env);
	name = get_value_in_variable("NAME", env);
	if (!name)
		name = get_value_in_variable("USER", env);
	name_dir = getcwd(NULL, 0);
	dir = ft_strnstr(name_dir, name, ft_strlen(name_dir));
	if (dir)
		dir = dir + ft_strlen(host) + 1;
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

	mini.token = NULL;
	mini.env = get_envp();
	while (1)
	{
		prompt = create_prompt(mini.env);
		input = readline(prompt);
		if (input[0])
		{
			add_history(input);
			if (!check_input(input))
			{
				free(input);
				free(prompt);
				continue ;
			}
			fill_struct(input, &mini.token);
			mark_tokens(mini.token);
			expander_va(&mini);
			check_commands(mini.token, &mini.env);
			free_list(mini.token);
			mini.token = NULL;
		}
		free(input);
		free(prompt);
	}
	free_env(mini.env);
	return (0);
}

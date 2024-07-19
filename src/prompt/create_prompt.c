/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:05:21 by yufonten          #+#    #+#             */
/*   Updated: 2024/07/12 14:07:58 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*create_prompt(t_env_list *env)
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
		dir = dir + ft_strlen(name);
	else
		dir = name_dir;
	prompt = organize_prompt(host, name, dir);
	free(name_dir);
	return (prompt);
}

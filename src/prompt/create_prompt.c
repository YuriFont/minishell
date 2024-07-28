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
	char	*temp;
	char	*resul_of_session;
	int		i;

	i = 0;
	temp = ft_strchr(host, '/') + 1;
	while (temp[i])
	{
		if (temp[i] == '.')
		{
			resul_of_session = ft_substr(temp, 0, i);
			break ;
		}
		i++;
	}
	return (resul_of_session);
}

char	*get_host_name(t_env_list *env)
{
	char	*host;

	host = get_value_in_variable("SESSION_MANAGER", env);
	if (host)
		host = get_local_of_session(host);
	else
		host = get_value_in_variable("LOGNAME", env);
	if (!host)
		host = ft_strdup("");
	else
		host = ft_strdup(host);
	return (host);
}

char	*get_username(t_env_list *env)
{
	char	*name;

	name = get_value_in_variable("NAME", env);
	if (!name)
		name = get_value_in_variable("USER", env);
	if (!name)
		name = ft_strdup("");
	else
		name = ft_strdup(name);
	return (name);
}

char	*get_new_host(char *host)
{
	char	*new_host;

	free(host);
	new_host = ft_strdup("Minihell");
	return (new_host);
}

char	*get_new_username(char *name)
{
	char	*new_username;

	free(name);
	new_username = ft_strdup("SegmentationFault");
	return (new_username);
}

char	*create_prompt(t_env_list *env)
{
	char	*host;
	char	*name;
	char	*dir;
	char	*name_dir;
	char	*prompt;

	host = get_host_name(env);
	name = get_username(env);
	if (ft_strlen(host) == 0 || ft_strlen(name) == 0)
	{
		host = get_new_host(host);
		name = get_new_username(name);
	}
	name_dir = getcwd(NULL, 0);
	dir = ft_strnstr(name_dir, name, ft_strlen(name_dir));
	if (dir)
		dir = dir + ft_strlen(name);
	else
		dir = name_dir;
	prompt = organize_prompt(host, name, dir);
	free(name_dir);
	free(name);
	free(host);
	return (prompt);
}

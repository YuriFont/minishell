/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:05:21 by yufonten          #+#    #+#             */
/*   Updated: 2024/08/20 14:48:06 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*organize_prompt(char *host, char *name, char *dir)
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

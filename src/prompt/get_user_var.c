/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:22:23 by erramos           #+#    #+#             */
/*   Updated: 2024/08/03 16:22:24 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_local_of_session(char *host)
{
	char	*temp;
	char	*resul_of_session;
	int		i;

	i = 0;
	temp = ft_strchr(host, '/') + 1;
	resul_of_session = NULL;
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

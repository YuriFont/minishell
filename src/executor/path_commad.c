/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_commad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:10:18 by erramos           #+#    #+#             */
/*   Updated: 2024/08/03 16:10:26 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path_command(t_token *token, char *paths)
{
	char	**splits;
	char	*path_command;
	char	*found;
	int		i;

	i = 0;
	splits = ft_split(paths, ':');
	while (splits[i])
	{
		path_command = ft_strjoin(splits[i], "/");
		path_command = ft_strjoinf(path_command, token->text);
		if (access(path_command, F_OK) == 0)
		{
			found = ft_strdup(path_command);
			free(path_command);
			free_matriz(splits);
			return (found);
		}
		free(path_command);
		i++;
	}
	free_matriz(splits);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/25 15:51:46 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 15:51:46 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_list(t_token *list)
{
	t_token	*aux;

	while (list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux->text);
		free(aux);
	}
}

void	free_env(t_env_list *list)
{
	t_env_list	*aux;

	while (list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux->variable);
		free(aux);
	}
}

int	get_my_pid()
{
	int		fd;
	char	*resp;
	int		pid;

	fd = open("/proc/self/stat", O_RDONLY);
	resp = malloc(sizeof(char) * 50);
	ft_memset(resp, 0, 50);
	read(fd, resp, 50);
	close(fd);
	pid = ft_atoi(resp);
	free(resp);
	resp = NULL;
	return (pid);
}

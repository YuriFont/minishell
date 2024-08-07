/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:51:46 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 15:51:46 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_my_pid(void)
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

int	everything_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	find_next_char(int i, char c, char *input)
{
	i++;
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

int	break_point_quotes(char c)
{
	if (c != ' ' && c != '\0' && c != '|' && c != '>' && c != '<')
		return (1);
	return (0);
}
/* 
	Sem uso 
*/

int	find_last_caracter(char *input, int i)
{
	char	c;

	if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		c = input[i];
	while (input[i] && input[i] == c)
		i++;
	return (i);
}

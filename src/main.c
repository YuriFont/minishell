/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:18:08 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 14:18:08 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
	(void)envp;
    char	*name;
    char	*user;
    char	*dir;

    name = getenv("NAME");
    user = getenv("LOGNAME");
    dir = getenv("PWD");
	dir += (6 + ft_strlen(name));
	printf("%s@%s:~%s$ ", name, user, dir);
    /*while (1)
    {
        
    }*/
    return (0);
}
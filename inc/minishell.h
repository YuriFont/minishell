/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:22:22 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/25 15:22:22 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_token
{
    int				token;
	char			*text;
    struct s_token	*next;
    struct s_token	*prev;
}   t_token;

/* utils.c */

/* utils_list.c */
t_token *find_last_node(t_token *head);

/* fill_struct.c */
void	fill_struct(char *input, t_token **data);

#endif
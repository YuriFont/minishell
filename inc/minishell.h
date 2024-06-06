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

typedef enum e_command
{
    PIPE,
    BUILTIN,
    ARGM,
    ENV_VA,
    WORD
} t_command;

typedef struct s_token
{
    int				token;
	char			*text;
    struct s_token	*next;
    struct s_token	*prev;
}   t_token;

typedef struct s_env_list
{
    char *variable;
    struct s_env_list *next;
}   t_env_list;

/* utils.c */

/* utils_list.c */
t_token *find_last_node(t_token *head);

/* fill_struct.c */
void	fill_struct(char *input, t_token **data);

void    free_list(t_token *list);
void    free_env(t_env_list *list);
void    check_builtins(t_token *token);
t_env_list      *get_envp();
char	*get_in_env(char *search, t_env_list *list);
void    print_env_list(t_env_list *list);

#endif
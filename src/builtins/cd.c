/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:16:06 by erramos           #+#    #+#             */
/*   Updated: 2024/08/26 20:25:52 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	move_to_old_directory(t_env_list *aux)
{
	char	*directory;

	if (!aux)
	{
		printf("cd :  OLDPWD not set\n");
		exit_status_repository(1);
		return (0);
	}
	directory = ft_strchr(aux->variable, '=') + 1;
	printf("%s\n", directory);
	if (chdir(directory) != 0)
		perror("cd");
	return (1);
}

int	verify_direction(t_token *directory,
	t_env_list *env, t_env_list *aux, char *old_dir)
{
	if (strncmp(directory->text, "-", ft_strlen(directory->text)) == 0)
	{
		if (!move_to_old_directory(aux))
		{
			free(old_dir);
			return (0);
		}
	}
	else if (chdir(directory->text) != 0)
	{
		perror("cd");
		exit_status_repository(1);
		return (0);
	}
	if (!aux)
	{
		add_new_variable(&env, "OLDPWD", old_dir, 1);
		return (0);
	}
	return (1);
}

void	change_pwd(t_env_list *env)
{
	t_env_list	*aux;
	char		*pwd;
	char		*current_directory;

	aux = get_in_env("PWD", env);
	if (!aux)
		return ;
	current_directory = getcwd(NULL, 0);
	pwd = change_value_of_variable(current_directory, aux->variable);
	free(current_directory);
	free(aux->variable);
	aux->variable = pwd;
}

int	move_to_directory(t_token *directory, t_env_list *env)
{
	char		*old_dir;
	char		*new_old_dir;
	t_env_list	*aux;

	old_dir = getcwd(NULL, 0);
	aux = get_in_env("OLDPWD", env);
	if (!verify_direction(directory, env, aux, old_dir))
		return (0);
	new_old_dir = change_value_of_variable(old_dir, aux->variable);
	free(old_dir);
	free(aux->variable);
	aux->variable = new_old_dir;
	change_pwd(env);
	return (1);
}

void	change_directory(t_token *directory, t_env_list *env)
{
	char		*dir;

	if (directory == NULL || directory->token == PIPE)
	{
		dir = get_value_in_variable("HOME", env);
		if (!dir)
			return (print_error_home_not_set());
		chdir(dir);
		exit_status_repository(0);
	}
	else if (directory->next == NULL
		|| (directory->next != NULL && directory->next->token == PIPE))
	{
		if (!move_to_directory(directory, env))
			return ;
		exit_status_repository(0);
	}
	else
	{
		ft_fprintf(2, "-mini: cd: too many arguments\n");
		exit_status_repository(1);
	}
}

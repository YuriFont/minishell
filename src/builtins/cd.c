#include "../../inc/minishell.h"

int	move_to_old_directory(t_env_list *aux)
{
	char	*directory;

	if (!aux)
	{
		printf("cd :  OLDPWD not set\n");
		return (0);
	}
	directory = ft_strchr(aux->variable, '=') + 1;
	printf("%s\n", directory);
	if (chdir(directory) != 0)
		perror("cd");
	return (1);
}

int	move_to_directory(t_token *directory, t_env_list *env)
{
	char		*old_dir;
	char		*new_old_dir;
	t_env_list	*aux;

	old_dir = getcwd(NULL, 0);
	aux = get_in_env("OLDPWD", env);
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
		return (0);
	}
	if (!aux)
	{
		add_new_variable(env, "OLDPWD", old_dir);
		free(old_dir);
		return (0);
	}
	new_old_dir = change_value_of_variable(old_dir, aux->variable);
	free(old_dir);
	free(aux->variable);
	aux->variable = new_old_dir;
	return (1);
}

void	change_directory(t_token *directory, t_env_list *env)
{
	char		*dir;

	if (directory == NULL)
	{
		dir = getenv("HOME");
		chdir(dir);
	}
	else if (directory->next == NULL)
	{
		if (!move_to_directory(directory, env))
			return ;
	}
	else
		printf("too many arguments\n");
}
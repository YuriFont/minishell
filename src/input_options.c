#include "../inc/minishell.h"

int	move_to_directory(t_token *directory, t_env_list *env)
{
	char		*old_dir;
	char		*new_old_dir;
	t_env_list	*aux;

	old_dir = getcwd(NULL, 0);
	if (chdir(directory->text) != 0)
	{
		perror("cd");
		return (0);
	}
	aux = get_in_env("OLDPWD", env);
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

void	check_builtins(t_token *token, t_env_list *env)
{
	if (ft_strncmp(token->text, "cd", 2) == 0)
		change_directory(token->next, env);
	if (ft_strncmp(token->text, "pwd", 3) == 0)
		printf("%s\n", getcwd(NULL, 0));
	if (ft_strncmp(token->text, "exit", 4) == 0)
	{
		free_list(token);
		free_env(env);
		rl_clear_history();
		exit(0);
	}
	if (ft_strncmp(token->text, "env", 3) == 0)
	{
		print_env_list(env);
	}
}

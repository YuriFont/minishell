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

/*
	Aqui esta entre mover para o diretorio anterio, que
	e  o cd com o " - ", se o antigo diretorio não existir
	ele apresenta o erro e não alterar o oldpwd, ate porque
	não existe, e retorna para função anterior(acho que tem um
	vazamento), no segundo if ele move para o novo diretorio,
	se oldpwd não existe (que esta armazenado na variavel
	aux) ele adiciona a nova variavel de ambiente
*/

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
		return (0);
	}
	if (!aux)
	{
		add_new_variable(env, "OLDPWD", old_dir);
		free(old_dir);
		return (0);
	}
	return (1);
}
/*
	Move para o diretorio. Antes pega o diretorio atual,
	que logo sera o novo diretorio anterior.
	E tambem tenta pegar o antigo diretorio anterior.
*/

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
	return (1);
}

/*
	Recebe o nó seguinte apos o cd (o diretorio no caso),
	se nenhum parametro e encontrado ele vai pra home do usuario,
	se o proximo for nulo quer dizer que foi passado corretamente
	o cd + diretorio, se passar mais de um argumento no cd aparece um
	erro. A env_list e passada para alterar a variavel de
	diretorio anterior(OLDPWD).
*/

void	change_directory(t_token *directory, t_env_list *env)
{
	char		*dir;

	if (directory == NULL)
	{
		dir = get_value_in_variable("HOME", env);
		if (!dir)
		{
			printf("minishell: cd: HOME not set\n");
			exit_status_repository(1);
			return ;
		}
		chdir(dir);
		exit_status_repository(0);
	}
	else if (directory->next == NULL)
	{
		if (!move_to_directory(directory, env))
			return ;
		exit_status_repository(0);
	}
	else
	{
		printf("too many arguments\n");
		exit_status_repository(1);
	}
}

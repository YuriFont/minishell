#include "../../inc/minishell.h"


int	count_of_args(t_token *list)
{
	int	i;
	t_token	*aux;

	i = 0;
	aux = list;
	while (aux && aux->token != PIPE && !(aux->token >= 4 && aux->token <= 7))
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

char	**create_args_options(char *path_command, t_token *token)
{
	char	**args;
	char	*is_ls;
	int		count_args;
	int		i;
	t_token *aux;

	i = 1;
	aux = token;
	count_args = count_of_args(token);
	is_ls = path_command;
	is_ls = is_ls + (ft_strlen(is_ls) - 2);
	if (ft_strncmp(is_ls, "ls", ft_strlen(is_ls)) == 0)
	{
		args = (char **)malloc(sizeof(char *) * (count_args + 3));
		args[0] = ft_strdup(path_command);
		args[1] = ft_strdup("--color=auto");
		while (++i <= (count_args + 1))
		{
			args[i] = ft_strdup(aux->text);
			aux = aux->next;
		}
	}
	else
	{
		args = (char **)malloc(sizeof(char *) * (count_args + 2));
		args[0] = ft_strdup(path_command);
		while (i <= (count_args))
		{
			args[i] = ft_strdup(aux->text);
			aux = aux->next;
			i++;
		}
	}
	args[i] = NULL;
	return (args);
}

char	**create_args(char *path_command, t_token *token)
{
	char	**args;
	char	*result;

	if (!token)
	{
		args = (char **)malloc(sizeof(char *) * 3);
		args[0] = ft_strdup(path_command);
		result = path_command;
		result = result + (ft_strlen(result) - 2);
		if (ft_strncmp(result, "ls", ft_strlen(result)) == 0)
		{
			args[1] = ft_strdup("--color=auto");
			args[2] = NULL;
		}
		else
			args[1] = NULL;
	}
	else
	{
		args = create_args_options(path_command, token);
	}
	return (args);
}

void	execute_command(char *command, char *path_command, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path_command, argv, env) == -1)
		{
			printf("%s: command not found\n", command);
			exit(127);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		exit_status_repository(WEXITSTATUS(status));
	}
}

void	read_command(t_token *token, t_env_list *list)
{
	char	**env;
	char	**path;
	int		i;
	char	*path_command;
	char	**argv;

	i = 0;
	argv = NULL;
	env = env_to_matriz(list);
	path = ft_split(get_value_in_variable("PATH", list), ':');
	path_command = ft_strjoin(path[i], "/");
	path_command = ft_strjoinf(path_command, token->text);
	while (path[i])
	{
		if (access(path_command, F_OK) == 0)
		{
			argv = create_args(path_command, token->next);
			rl_on_new_line();
			execute_command(token->text, path_command, argv, env);
			break ;
		}
		i++;
		if (path[i])
		{
			free(path_command);
			path_command = ft_strjoin(path[i], "/");
			path_command = ft_strjoinf(path_command, token->text);
		}
	}
	free(path_command);
	if (!argv)
	{
		path_command = ft_strjoinf(getcwd(NULL, 0), "/");
		path_command = ft_strjoinf(path_command, token->text);
		argv = create_args(path_command, token);
		execute_command(token->text, path_command, argv, env);
		free(path_command);
	}
	free_matriz(path);
	free_matriz(env);
	free_matriz(argv);
}

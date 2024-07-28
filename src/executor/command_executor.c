#include "../../inc/minishell.h"

void	handle_if_signal(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			printf("Quit\n");
			exit_status_repository(131);
		}
		else if (WTERMSIG(status) == 2)
		{
			printf("\n");
			exit_status_repository(130);
		}
	}
}

void	execute_command(char *command, char *path_command, char **argv,
		char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
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
		handle_if_signal(status);
	}
}

int	count_of_args(t_token *list)
{
	int		i;
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

char	**elaborating_args(t_token *token, char *path_command)
{
	t_token	*aux;
	int		count_args;
	int		i;
	char	**args;

	i = 1;
	aux = token;
	count_args = count_of_args(token);
	args = (char **)malloc(sizeof(char *) * (count_args + 3));
	args[0] = ft_strdup(path_command);
	args[1] = ft_strdup("--color=auto");
	while (++i <= (count_args + 1))
	{
		args[i] = ft_strdup(aux->text);
		aux = aux->next;
	}
	args[i] = NULL;
	return (args);
}

char	**create_args_options(char *path_command, t_token *token)
{
	char	**args;
	char	*is_ls;
	int		count_args;
	int		i;
	t_token	*aux;

	i = 1;
	aux = token;
	count_args = count_of_args(token);
	is_ls = path_command + (ft_strlen(path_command) - 2);
	if (ft_strncmp(is_ls, "ls", ft_strlen(is_ls)) == 0)
		args = elaborating_args(token, path_command);
	else
	{
		args = (char **)malloc(sizeof(char *) * (count_args + 2));
		args[0] = ft_strdup(aux->text);
        aux = aux->next;
        while ((i < (count_args)) && aux)
		{
			args[i] = ft_strdup(aux->text);
             printf("%s\n", aux->text);
            aux = aux->next;
            i++;
		}
   //             printf("%s\n", args[0]);
   //      printf("%s\n", args[1]);
            args[i] = NULL;
            printf("%s   %d\n", args[i], i);
	}
	return (args);
}

char	**create_args(char *path_command, t_token *token)
{
	char	**args;
	char	*result;

	if (!token->next)
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
       // printf("%s\n", token->text);
		args = create_args_options(path_command, token);
	}

	return (args);
}

int	is_absolute_path(t_token *token, t_env_list *list)
{
	char	**argv;
	char	**env;
	t_token	*temp;

	temp = token;
	if (temp->text[0] != '/')
		return (0);
	argv = create_args_options(temp->text, temp->next);
	env = env_to_matriz(list);
	execute_command(temp->text, temp->text, argv, env);
	free_matriz(env);
	free_matriz(argv);
	return (1);
}

int	is_current_directory(t_token *token, t_env_list *list)
{
	char	**argv;
	char	**env;
	t_token	*temp;

	temp = token;
	if (temp->text[0] != '.' && temp->text[1] != '/')
		return (0);
	argv = create_args_options(temp->text, temp->next);
	env = env_to_matriz(list);
	execute_command(temp->text, temp->text, argv, env);
	free_matriz(env);
	free_matriz(argv);
	return (1);
}

char	*get_path_command(t_token *token, char *paths)
{
	char	**splits;
	char	*path_command;
	char	*found;
	int		i;

	i = 0;
	splits = ft_split(paths, ':');
	while (splits[i])
	{
		path_command = ft_strjoin(splits[i], "/");
		path_command = ft_strjoinf(path_command, token->text);
		if (access(path_command, F_OK) == 0)
		{
			found = ft_strdup(path_command);
			free(path_command);
			free_matriz(splits);
			return (found);
		}
		free(path_command);
		i++;
	}
	free_matriz(splits);
	return (NULL);
}

void	run_command(t_token *token, t_env_list *env, char *path)
{
	char	**argv;
	char	**env_mat;

 //   printf("%s\n", token->text);
	argv = create_args(path, token);
	env_mat = env_to_matriz(env);
	execute_command(token->text, path, argv, env_mat);
	free_matriz(argv);
	free_matriz(env_mat);
}

void	read_command(t_token *token, t_env_list *list)
{
	char	*path;
	char	*path_command;

	if (is_absolute_path(token, list))
		return ;
	if (is_current_directory(token, list))
		return ;
	path = get_value_in_variable("PATH", list);
	if (!path)
	{
		printf("%s :Command not found\n", token->text);
		exit_status_repository(127);
		return ;
	}
	path_command = get_path_command(token, path);
	if (!path_command)
	{
		printf("%s :Command not found\n", token->text);
		exit_status_repository(127);
		return ;
	}
	run_command(token, list, path_command);
	free(path_command);
}

#include "../../inc/minishell.h"

char	**create_args(char *path_command)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * 2);
	args[0] = ft_strdup(path_command);
	args[1] = NULL;
	return (args);
}

void	execute_command(char *path_command, char **argv, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path_command, argv, env);
		exit(42);
	}
	else
	{
		wait(NULL);
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
			argv = create_args(path_command);
			rl_on_new_line();
			execute_command(path_command, argv, env);
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
		argv = create_args(path_command);
		execute_command(path_command, argv, env);
		free(path_command);
	}
	free_matriz(path);
	free_matriz(env);
	free_matriz(argv);
}

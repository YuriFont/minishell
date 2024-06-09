#include "../inc/minishell.h"

void	change_directory(t_token *directory)
{
	char	*dir;

	if (directory == NULL)
	{
		dir = getenv("HOME");
		chdir(dir);
	}
	else if (directory->next == NULL)
	{
		if (chdir(directory->text) != 0)
			perror("cd");
	}
	else
		printf("too many arguments\n");
}

void	check_builtins(t_token *token)
{
	if (ft_strncmp(token->text, "cd", 2) == 0)
		change_directory(token->next);
	if (ft_strncmp(token->text, "pwd", 3) == 0)
		printf("%s\n", getcwd(NULL, 0));
	if (ft_strncmp(token->text, "exit", 4) == 0)
	{
		free_list(token);
		rl_clear_history();
		exit(0);
	}
}

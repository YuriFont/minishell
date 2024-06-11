#include "../inc/minishell.h"

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
	if (ft_strncmp(token->text, "echo", 4) == 0)
	{
		print_echo(token->next);
	}
}

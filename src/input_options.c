#include "../inc/minishell.h"


void	check_commands(t_token *token, t_env_list **env)
{
	if (!check_builtins(token, env))
		read_command(token, *env);
}

int	check_builtins(t_token *token, t_env_list **env)
{
	if (ft_strncmp(token->text, "cd", 2) == 0)
		change_directory(token->next, *env);
	else if (ft_strncmp(token->text, "pwd", 3) == 0)
		printf("%s\n", getcwd(NULL, 0));
	else if (ft_strncmp(token->text, "exit", 4) == 0)
	{
		free_list(token);
		free_env(*env);
		rl_clear_history();
		exit(0);
	}
	else if (ft_strncmp(token->text, "env", 3) == 0)
	{
		print_env_list(*env);
	}
	else if (ft_strncmp(token->text, "echo", 4) == 0)
	{
		print_echo(token->next);
	}
	else if (ft_strncmp(token->text, "export", 6) == 0)
	{
		insert_in_env(*env, token->next);
	}
	else if (ft_strncmp(token->text, "unset", 5) == 0)
		remove_variable_env(token->next, env);
	else
		return (0);
	return (1);
}

#include "../inc/minishell.h"

// int	check_is_redirect(t_token *token)
// {
// 	t_token	*temp;

// 	temp = token;
// 	while (temp)
// 	{
// 		if (temp->token == REDIRECT && temp->next != NULL)
// 			return (1);
// 		temp = temp->next;
// 	}
// 	return (0);
// }

void	check_commands(t_token *token, t_env_list **env)
{
	// if (check_is_redirect(token))
 	// 	redirect(token, env);
	if (!check_builtins(token, env))
		read_command(token, *env);
}

int	check_builtins(t_token *token, t_env_list **env)
{
	if (ft_strncmp(token->text, "cd", 3) == 0)
		change_directory(token->next, *env);
	else if (ft_strncmp(token->text, "pwd", 4) == 0)
		printf("%s\n", getcwd(NULL, 0));
	else if (ft_strncmp(token->text, "exit", 5) == 0)
	{
		exe_exit(token, *env);
	}
	else if (ft_strncmp(token->text, "env", 4) == 0)
	{
		print_env_list(*env);
	}
	else if (ft_strncmp(token->text, "echo", 5) == 0)
	{
		print_echo(token->next);
	}
	else if (ft_strncmp(token->text, "export", 7) == 0)
	{
		insert_in_env(*env, token->next);
	}
	else if (ft_strncmp(token->text, "unset", 6) == 0)
		remove_variable_env(token->next, env);
	else
		return (0);
	return (1);
}

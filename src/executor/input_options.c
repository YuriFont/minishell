#include "../../inc/minishell.h"

int	get_fd(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->fd_out != STDOUT_FILENO)
			return (temp->fd_out);
		temp = temp->next;
	}
	return (1);
}

int	check_builtins(t_token *token, t_env_list **env)
{
	if (ft_strncmp(token->text, "cd", 3) == 0)
		change_directory(token->next, *env);
	else if (ft_strncmp(token->text, "pwd", 4) == 0)
		exe_pwd(token);
	else if (ft_strncmp(token->text, "exit", 5) == 0)
		exe_exit(token, *env);
	else if (ft_strncmp(token->text, "env", 4) == 0)
		print_env_list(*env);
	else if (ft_strncmp(token->text, "echo", 5) == 0)
		print_echo(token->next);
	else if (ft_strncmp(token->text, "export", 7) == 0)
		insert_in_env(*env, token->next);
	else if (ft_strncmp(token->text, "unset", 6) == 0)
		remove_variable_env(token->next, env);
	else
		return (0);
	return (1);
}

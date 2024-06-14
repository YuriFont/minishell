#include "../../inc/minishell.h"

int	verify_nome_of_variable_is_valid(char *name)
{
	(void)name;
	return (1);
}

int	valid_new_variable(char *new_variable)
{
	char	*find_equal;
	char	*name_variable;

	find_equal = ft_strchr(new_variable, '=');
	if (!find_equal)
		return (0);
	name_variable = ft_substr(new_variable, 0,
			ft_strlen(new_variable) - ft_strlen(find_equal));
	(void)name_variable;
	return (1);
}

void	insert_in_env(t_env_list *env, t_token *token)
{
	(void)env;
	if (!token)
		return ;
	valid_new_variable(token->text);
}

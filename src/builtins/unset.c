#include "../../inc/minishell.h"

/*
	Procura a variavel de ambiente na env_list
	 e a remove, tem mais de 25 linhas :(
*/

void	remove_variable_env(t_token *node, t_env_list *env)
{
	t_env_list	*temp;
	t_env_list	*prev;
	t_env_list	*remove;
	char		*variable;

	if (!node)
		return ;
	variable = node->text;
	temp = env;
	while (env && ft_strncmp(env->variable, variable,
			ft_strlen(variable)) != 0)
	{
		prev = env;
		env = env->next;
	}
	remove = env;
	if (temp == remove)
	{
		env = env->next;
		free(remove);
	}
	else
	{
		prev->next = env->next;
		free(remove);
		env = temp;
	}
}

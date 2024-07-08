#include "../../inc/minishell.h"

int	verify_nome_of_variable_is_valid(char *name)
{
	char	*not_valid;
	int		i;
	int		j;

	not_valid = NO_VALID_CHAR;
	i = 0;
	while (name[i])
	{
		j = 0;
		while (not_valid[j])
		{
			if (name[i] == not_valid[j])
			{
				printf("export: `%s': not a valid identifier\n", name);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
	Valida apenas o nome da "variavel de ambiente"
*/

char	*valid_new_variable(char *new_variable)
{
	char	*find_equal;
	char	*name_variable;

	find_equal = ft_strchr(new_variable, '=');
	if (!find_equal)
		return (NULL);
	name_variable = ft_substr(new_variable, 0,
			ft_strlen(new_variable) - ft_strlen(find_equal));
	if (!verify_nome_of_variable_is_valid(name_variable))
	{
		free(name_variable);
		return (NULL);
	}
	return (name_variable);
}

void	change_value_of_env(t_env_list *env, char *variable_change)
{
	char	*temp;

	temp = env->variable;
	env->variable = variable_change;
	free(temp);
}

int	verify_exist_in_env(char *name, t_env_list *env, t_token *token)
{
	t_env_list	*result;
	char		*value;
	char		*value_change;

	result = get_in_env(name, env);
	if (!result)
		return (0);
	value = ft_strchr(token->text, '=') + 1;
	value_change = change_value_of_variable(value, name);
	change_value_of_env(result, value_change);
	free(name);
	return (1);
}

/*
	Inserir uma nova "variavel de ambiente" ao 
	digitar export + <nome da variavel=conteudo da variavel>,
	necessario verificar se a variavel ja existe
	 e alterar apenas o valor ao invez de mallocar.
*/

void	insert_in_env(t_env_list *env, t_token *token)
{
	char	*name;
	char	*value;

	if (!token)
		return ;
	name = valid_new_variable(token->text);
	if (!name)
		return ;
	if (verify_exist_in_env(name, env, token))
		return ;
	value = ft_strchr(token->text, '=') + 1;
	add_new_variable(env, name, value);
	free(name);
}

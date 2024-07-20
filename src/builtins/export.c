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

char	*get_name_of_variable(char *variable)
{
	char	*find_equal;
	char	*name_variable;

	find_equal = ft_strchr(variable, '=');
	if (!find_equal)
		return (NULL);
	name_variable = ft_substr(variable, 0,
			ft_strlen(variable) - ft_strlen(find_equal));
	return (name_variable);
}

/*
	Valida apenas o nome da "variavel de ambiente"
*/

char	*valid_new_variable(char *new_variable)
{
	char	*name_variable;

	name_variable = get_name_of_variable(new_variable);
	if (!name_variable)
		return (NULL);
	if (!verify_nome_of_variable_is_valid(name_variable))
	{
		free(name_variable);
		exit_status_repository(1);
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

void	print_export(t_env_list *env)
{
	t_env_list	*temp;
	char		*print_variable;
	char		*name;

	temp = env;
	while (temp)
	{
		name = get_name_of_variable(temp->variable);
		print_variable = ft_strdup("declare -x ");
		print_variable = ft_strjoinf(print_variable, name);
		print_variable = ft_strjoinf(print_variable, "=\"");
		print_variable = ft_strjoinf(print_variable,
				get_value_in_variable(name, env));
		print_variable = ft_strjoinf(print_variable, "\"");
		printf("%s\n", print_variable);
		free(print_variable);
		free(name);
		temp = temp->next;
	}
	exit_status_repository(0);
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
	{
		print_export(env);
		exit_status_repository(0);
		return ;
	}
	name = valid_new_variable(token->text);
	if (!name)
		return ;
	if (verify_exist_in_env(name, env, token))
		return ;
	value = ft_strchr(token->text, '=') + 1;
	add_new_variable(env, name, value);
	free(name);
	exit_status_repository(0);
}

#include "../../inc/minishell.h"

t_env_list	*get_envp(void)
{
	extern char		**environ;
	t_env_list		*head;
	t_env_list		*prev;
	t_env_list		*node;
	int				i;

	i = 0;
	head = NULL;
	prev = NULL;
	node = NULL;
	while (environ[i])
	{
		node = malloc(sizeof(t_env_list));
		if (!node)
			return (NULL);
		node->variable = ft_strdup(environ[i]);
		node->next = NULL;
		if (!head)
			head = node;
		else
			prev->next = node;
		prev = node;
		i++;
	}
	return (head);
}

t_env_list	*get_in_env(char *search, t_env_list *list)
{
	t_env_list	*aux;

	aux = list;
	while (aux)
	{
		if (!ft_strncmp(search, aux->variable, ft_strlen(search)))
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

char	*get_value_in_variable(char *variable, t_env_list *list)
{
	char		*value;
	t_env_list	*aux;

	aux = get_in_env(variable, list);
	if (!aux)
		return (NULL);
	value = ft_strchr(aux->variable, '=');
	if (!value)
		return (NULL);
	return (value + 1);
}

void	print_env_list(t_env_list *list)
{
	t_env_list	*aux;

	aux = list;
	while (aux)
	{
		printf("%s\n", aux->variable);
		aux = aux->next;
	}
}

char	*change_value_of_variable(char *new_value, char *variable)
{
	char	*name;
	char	*new_variable;
	char	*result;

	name = ft_strrchr(variable, '=');
	if (name)
	{
		result = ft_substr(variable, 0, ft_strlen(variable) - ft_strlen(name));
		new_variable = ft_strjoinf(result, "=");
	}
	else
	{
		result = variable;
		new_variable = ft_strjoin(result, "=");
	}
	new_variable = ft_strjoinf(new_variable, new_value);
	return (new_variable);
}

void	add_new_variable(t_env_list *env, char *variable, char *value)
{
	t_env_list	*aux;
	t_env_list	*new_node;
	char		*new_variable;

	new_variable = change_value_of_variable(value, variable);
	aux = find_last_node_in_env(env);
	new_node = malloc(sizeof(t_env_list));
	new_node->variable = new_variable;
	new_node->next = NULL;
	aux->next = new_node;
}

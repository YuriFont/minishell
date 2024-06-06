#include "../../inc/minishell.h"

t_env_list	*get_envp()
{
	extern char **environ;
	t_env_list *head;
	t_env_list *prev;
	t_env_list *node;
	int		i;

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

char	*get_in_env(char *search, t_env_list *list)
{
	t_env_list	*aux;

	aux = list;
	while (aux)
	{
		if (!ft_strncmp(search, aux->variable, ft_strlen(search)))
			return (aux->variable);
		aux = aux->next;
	}
	return (NULL);
}

void	print_env_list(t_env_list *list)
{
	t_env_list *aux;

	aux = list;
	while (aux)
	{
		printf("%s\n", aux->variable);
		aux = aux->next;
	}
}
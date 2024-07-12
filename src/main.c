/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:18:08 by yufonten          #+#    #+#             */
/*   Updated: 2024/05/26 17:20:19 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char		*prompt;
	char		*input;
	t_minishell	mini;
	
	mini.token = NULL;
	mini.env = get_envp();
	input = NULL;
	handler_signals();
	while (1)
	{
		prompt = create_prompt(mini.env);
		input = readline(prompt);
		if (!input)
		{
			printf("exit\n");
			exe_exit(mini.token, mini.env);
		}
		if (parse(input, prompt, &mini))
			continue ;
		check_commands(mini.token, &mini.env);
		free_list(mini.token);
		mini.token = NULL;
		input = NULL;
	}
	free_env(mini.env);
	return (0);
}

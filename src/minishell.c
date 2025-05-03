/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/02 20:55:07 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_command	*complex_command;
	t_list		*env_list;

	(void)ac;
	(void)av;
	env_list = catch_env(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			free(input);
			printf("\nSaindo do minishell...\n");
			break ;
		}
		if (*input)
			add_history(input);
		complex_command = parser(input, env_list);
		if (!complex_command)
		{
			free(input);
			continue ;
		}
		print_commands(complex_command);
		free_complex_command(complex_command);
		free(input);
	}
	free_env_list(env_list);
	return (0);
}

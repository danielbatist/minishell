/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/10 18:39:42 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_exit(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

static void	process_input(char *input, t_list *env_list)
{
	t_command	*complex_command;

	if (*input)
		add_history(input);
	complex_command = parser(input, env_list);
	if (!complex_command)
		return ;
	print_commands(complex_command);
	free_complex_command(complex_command);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_list		*env_list;

	(void)ac;
	(void)av;
	env_list = catch_env(envp);
	while (1)
	{
		set_signal();
		input = readline("minishell> ");
		if (handle_exit(input))
			break ;
		process_input(input, env_list);
		free(input);
	}
	free_env_list(env_list);
	return (0);
}

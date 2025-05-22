/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/21 13:09:16 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_exit(char *input, t_list *env_list)
{
	printf("exit\n");
	if (input)
		free(input);
	redirects_token(&env_list);
	exit(0);
}

static void	process_input(char *input, t_list *env_list)
{
	t_command	*complex_command;
	int			i;

	if (*input)
		add_history(input);
	complex_command = parser(input, env_list);
	if (!complex_command)
		return ;
	i = 0;
	while (complex_command[i].simple_command)
		execute_command(&complex_command[i++]);
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
		if (!input)
		{
			printf("readline retornou NULL\n");
			handle_exit(NULL, env_list);
		}
		process_input(input, env_list);
		free(input);
	}
	return (0);
}

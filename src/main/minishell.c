/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/06/04 12:16:12 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_list		*env_list;

	(void)ac;
	(void)av;
	env_list = catch_env(envp);
	while (1)
	{
		set_signal_readline();
		input = readline("minishell> ");
		if (!input)
			handle_exit(NULL, env_list);
		set_signal_exec_parent();
		process_input(input, env_list);
		free(input);
	}
	return (0);
}

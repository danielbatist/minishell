/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/06/11 22:32:14 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static void	print_pwd(void)
{
	int		i;
	char	*pwd;
	i = 0;
	pwd = getcwd(NULL, 0);
	if (ft_strncmp(pwd, "/home/eteofilo/", ft_strlen(pwd)) == 0)
	{
		free(pwd);
		pwd = ft_strdup("~");
	}
	else
		i = 15;
	set_signal_readline();
	ft_printf_fd(1, "\033[38;2;173;255;47m\001\033[1m\002"
		"%s"
		"\001\033[0m\002\n", pwd + i);
	free(pwd);
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
		print_pwd();
		input = readline("\033[38;2;135;206;250m\001\033[1m\002"
			">"
			"\001\033[0m\002 ");
		if (!input)
			handle_exit(NULL, env_list);
		set_signal_exec_parent();
		process_input(input, env_list);
		free(input);
	}
	return (0);
}

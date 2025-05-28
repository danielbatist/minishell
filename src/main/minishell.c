/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/28 18:58:23 by dbatista         ###   ########.fr       */
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

t_command	*input_and_parser(t_exec *data, char *input, t_list *env_list)
{
	t_command	*cmd;
	int			i;

	if (*input)
		add_history(input);
	cmd = parser(input, env_list);
	if (!cmd)
		return (NULL);
	i = 0;
	data->is_pipe = get_pipefd(cmd, &data->pipefd);
	data->pids = malloc(sizeof(pid_t) * (data->is_pipe + 1));
	if (!data->pids)
	{
		free(data);
		return (NULL);
	}
	ft_bzero(data->pids, sizeof(pid_t) * (data->is_pipe + 1));
	return (cmd);
}

t_exec	*init_exec_data(void)
{
	t_exec		*data;

	data = (t_exec *)malloc(sizeof(t_exec));
	if (!data)
		return (NULL);
	(data)->is_pipe = 0;
	(data)->is_builtin = 0;
	(data)->pipefd = NULL;
	(data)->pids = NULL;
	return (data);
}

void	process_input(char *input, t_list *env_list)
{
	t_command	*cmd;
	t_exec		*data;

	data = init_exec_data();
	cmd = input_and_parser(data, input, env_list);
	if (!cmd)
	{
		free(data);
		return ;
	}
	execute_commands(cmd, data, env_list);
	print_commands(cmd);
	free_complex_command(cmd);
	free_pipes(data->pipefd, data->is_pipe);
	free(data->pids);
	free(data);
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
			handle_exit(NULL, env_list);
		process_input(input, env_list);
		free(input);
	}
	return (0);
}

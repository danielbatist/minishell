/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:34:00 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 18:03:12 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_exit(char *input, t_list *env_list)
{
	printf("exit\n");
	if (input)
		free(input);
	free_env_list(env_list);
	exit(0);
}


t_command	*input_and_parser(char *input, t_list *env_list)
{
	t_command	*cmd;

	if (*input)
		add_history(input);
	cmd = parser(input, env_list);
	if (!cmd)
		return (NULL);
	return (cmd);
}

t_exec	*init_exec_data(t_command *cmd)
{
	t_exec		*data;

	data = (t_exec *)malloc(sizeof(t_exec));
	if (!data)
		return (NULL);
	data->is_pipe = 0;
	data->is_builtin = 0;
	data->pipefd = NULL;
	data->pids = NULL;
	data->is_pipe = get_pipefd(cmd, &data->pipefd);
	data->pids = malloc(sizeof(pid_t) * (data->is_pipe + 1));
	if (!data->pids)
	{
		free(data);
		return (NULL);
	}
	ft_bzero(data->pids, sizeof(pid_t) * (data->is_pipe + 1));
	return (data);
}

void	process_input(char *input, t_list *env_list)
{
	t_command	*cmd;
	t_exec		*data;

	cmd = input_and_parser(input, env_list);
	if (!cmd)
		return ;
	data = init_exec_data(cmd);
	cmd->data = data;
	execute_commands(cmd, data, env_list);
	//print_commands(cmd);
	free_complex_command(cmd);
	free(data->pipefd);
	free(data->pids);
	free(data);
}

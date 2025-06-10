/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/09 15:20:39 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void 	dup2_pipes(t_pipefd *pipefd, int is_pipe, int *i)
{
	if (*i > 0 && is_pipe > 0)
		dup2(pipefd[*i - 1].fd[0], STDIN_FILENO);
	if (*i < is_pipe)
		dup2(pipefd[*i].fd[1], STDOUT_FILENO);
}

void 	close_pipes(t_pipefd *pipefd, int n_of_pipes)
{
	int	i;

	i = 0;
	while (i < n_of_pipes)
	{
		close(pipefd[i].fd[0]);
		close(pipefd[i].fd[1]);
		i++;
	}
}

int	check_error_heredoc(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].simple_command)
	{
		if (cmd[i].error_flag)
		{
			set_exit_status(130);
			return (1);
		}
		i++;
	}
	return (0);
}

void	execute_commands(t_command *cmd, t_exec *data, t_list *env_list)
{
	int	i;

	i = 0;
	while (cmd[i].simple_command)
		cmd[i++].env_list = env_list;
	if (check_error_heredoc(cmd))
		return ;
	i = 0;
	while ((cmd[i].simple_command))
	{
		if (check_error_flag(cmd, &i))
			continue ;
		if (execute_builtins_in_parent(cmd, data, &i))
			continue ;
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			execute_child(cmd, i, data->is_pipe, data->pipefd);
		else
			clean_heredoc(&cmd[i]);
		i++;
	}
	execute_parent(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:22:50 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/09 22:13:14 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_parent(t_exec *data)
{
	int		j;
	int		status;

	close_pipes(data->pipefd, data->is_pipe);
	j = 0;
	status = 0;
	while (j <= data->is_pipe)
	{
		waitpid(data->pids[j], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status))
		{
			write(1, "\n", 1);
			set_exit_status(128 + WTERMSIG(status));
		}
		else if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status));
		j++;
	}
}

int	execute_builtins_in_parent(t_command *cmd, t_exec *data, int *i)
{
	int	status;
	int	save_stdout;

	if (data->is_pipe == 0 && is_builtins(cmd[*i].simple_command[0]))
	{
		if (ft_strcmp(cmd[*i].simple_command[0], "exit") == 0)
		{
			status = ft_exit(&cmd[*i]);
			set_exit_status(status);
			clean_heredoc(&cmd[*i]);
			return (1);
		}
		open_redirect(&cmd[*i]);
		save_stdout = dup(STDOUT_FILENO);
		dup2_redirect(&cmd[*i]);
		set_exit_status(exec_builtins(&cmd[*i]));
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdout);
		clean_heredoc(&cmd[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}

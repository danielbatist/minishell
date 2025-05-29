/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/29 17:39:07 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	execute_parent(t_exec *data, t_command *cmd, int *i)
{
	int		j;

	j = 0;
	clean_heredoc(cmd);
	if (*i > 0)
		close(data->pipefd[*i - 1].fd[0]);
	if (*i < data->is_pipe)
		close(data->pipefd[*i].fd[1]);
	while (j <= data->is_pipe)
	{
		waitpid(data->pids[j], NULL, 0);
		j++;
	}
}

void	execute_child(t_command *cmd, int i, int is_pipe, t_pipefd *pipefd)
{
	char	*path;
	char	**envp;
	int		j;

	if (open_redirect(&cmd[i]) < 0)
		exit (1);
	if (cmd[i].fd_in == -1 && i > 0 && is_pipe > 0)
		dup2(pipefd[i - 1].fd[0], STDIN_FILENO);
	if (cmd[i].fd_out == -1 && i < is_pipe)
		dup2(pipefd[i].fd[1], STDOUT_FILENO);
	dup_redirect(&cmd[i]);
	j = 0;
	while (j < is_pipe && is_pipe > 0)
	{
		close(pipefd[j].fd[0]);
		close(pipefd[j].fd[1]);
		j++;
	}
	if (cmd[i].simple_command && cmd[i].simple_command[0])
	{
		envp = get_envp(cmd[i].env_list);
		path = get_path(cmd[i].simple_command[0], cmd[i].env_list);
		if (!path)
		{
			ft_printf_fd(2, "minishell: command not found:");
			ft_printf_fd(2, "%s\n", cmd[i].simple_command[0]);
			free_exec(envp);
			exit(127);
		}
		execve(path, cmd->simple_command, envp);
		free_exec(&path);
		free_exec(envp);
		exit(1);
	}
	exit(0);
}

void	execute_commands(t_command *cmd, t_exec *data, t_list *env_list)
{
	int	i;

	i = 0;
	while (cmd[i].simple_command)
		cmd[i++].env_list = env_list;
	i = 0;
	while ((cmd[i].simple_command))
	{
		if (cmd[i].error_flag)
		{
			clean_heredoc(&cmd[i]);
			i++;
			continue ;
		}
		data->is_builtin = FALSE;
		if (data->is_pipe > 0 || !data->is_builtin)
		{
			data->pids[i] = fork();
			if (data->pids[i] == 0)
				execute_child(cmd, i, data->is_pipe, data->pipefd);
			else
				execute_parent(data, cmd, &i);
			i++;
		}
	}
}


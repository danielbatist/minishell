/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/03 20:41:59 by dbatista         ###   ########.fr       */
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


void	execute_parent(t_exec *data)
{
	int		j;

	close_pipes(data->pipefd, data->is_pipe);
	j = 0;
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

	dup2_pipes(pipefd, is_pipe, &i);
	close_pipes(pipefd, is_pipe);
	if (open_redirect(&cmd[i]) < 0)
		exit (1);
	dup2_redirect(&cmd[i]);
	if (cmd[i].simple_command && cmd[i].simple_command[0])
	{
		envp = get_envp(cmd[i].env_list);
		path = get_path(cmd[i].simple_command[0], cmd[i].env_list);
		if (!path)
		{
			ft_printf_fd(2, "%s: command not found\n", cmd[i].simple_command[0]);
			free_exec(envp);
			exit(127);
		}
		//ft_printf_fd(2, "Executando: %s\n", cmd[i].simple_command[0]);
		execve(path, cmd[i].simple_command, envp);
		free(path);
		free_exec(envp);
		exit(1);
	}
	exit(0);
}

void	execute_commands(t_command *cmd, t_exec *data, t_list *env_list)
{
	int	i;
	int save_stdout;

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
		if (data->is_pipe == 0 && is_builtins(cmd[i].simple_command[0]))
		{
			open_redirect(&cmd[i]);
			save_stdout = dup(STDOUT_FILENO);
			dup2_redirect(&cmd[i]);
			exec_builtins(&cmd[i]);
			dup2(save_stdout, STDOUT_FILENO);
			clean_heredoc(&cmd[i]);
			i++;
			continue ;
		}
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			execute_child(cmd, i, data->is_pipe, data->pipefd);
		else
			clean_heredoc(&cmd[i]);
		i++;
	}
	execute_parent(data);
}


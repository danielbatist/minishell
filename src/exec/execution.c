/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/27 20:25:55 by dbatista         ###   ########.fr       */
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
	int		j;

	if (i > 0 && is_pipe > 0)
		dup2(pipefd[i - 1].fd[0], STDIN_FILENO);
	if (i < is_pipe)
		dup2(pipefd[i].fd[1], STDOUT_FILENO);
	j = 0;
	while (j < is_pipe && is_pipe > 0)
	{
		close(pipefd[j].fd[0]);
		close(pipefd[j].fd[1]);
		j++;
	}
	if (open_redirect(&cmd[i]) < 0)
		exit (1);
	dup_redirect(&cmd[i]);
	if (cmd[i].simple_command && cmd[i].simple_command[0])
	{
		ft_printf_fd(2, "Executando: %s\n", cmd[i].simple_command[0]);
		execvp(cmd[i].simple_command[0], cmd[i].simple_command);
	}
	ft_printf_fd(2, "minishell: Erro ao executar o comando: %s\n", cmd[i].simple_command[0]);
	exit(1);
}

void	execute_commands(t_command *cmd, t_exec *data)
{
	int	i;

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


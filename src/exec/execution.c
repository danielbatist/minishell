/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/26 17:54:33 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_parent(t_command *cmd, int i, int is_pipe, t_pipefd *pipefd)
{
	clean_heredoc(&cmd[i]);
	if (i > 0)
		close(pipefd[i - 1].fd[0]);
	if (i < is_pipe)
		close(pipefd[i].fd[1]);
}

static void	exec_child(t_command *cmd, int i, int is_pipe, t_pipefd *pipefd)
{
	int	j;
	int	builtin;

	if (i > 0 && is_pipe > 0)
		dup2(pipefd[i - 1].fd[0], STDIN_FILENO);
	if (i < is_pipe)
		dup2(pipefd[i].fd[1], STDOUT_FILENO);
	j = 0;
	while (j < is_pipe)
	{
		close(pipefd[j].fd[0]);
		close(pipefd[j].fd[1]);
		j++;
	}
	if (open_redirect(&cmd[i]) < 0)
		exit(1);
	dup_redirect(&cmd[i]);
	if (cmd[i].simple_command && cmd[i].simple_command[0])
	{
		ft_printf_fd(2, "Executando: %s\n", cmd[i].simple_command[0]);
		builtin = is_builtins(cmd[i].simple_command[0], cmd[i].simple_command);
		if (builtin == 0)
			execvp(cmd[i].simple_command[0], cmd[i].simple_command);
	}
	ft_printf_fd(2, "minishell: Erro ao executar o comando: %s\n", cmd[i].simple_command[0]);
	exit(1);
}

void	execute_commands(t_command *cmd, int is_pipe, t_pipefd *pipefd, pid_t *pids)
{
	int	i;
	int	builtin;

	i = 0;
	builtin = 0;
	while (cmd[i].simple_command)
	{
		if (cmd[i].error_flag)
		{
			clean_heredoc(&cmd[i]);
			i++;
			continue ;
		}
		if (is_pipe == 0)
			builtin = is_builtins(cmd[i].simple_command[0], cmd[i].simple_command);
		if (builtin == 0)
		{
			pids[i] = fork();
			if (pids[i] == 0)
				exec_child(cmd, i, is_pipe, pipefd);
			else
				handle_parent(cmd, i, is_pipe, pipefd);
		}
		i++;
	}
}

/*void	execute_external_command(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (open_redirect(cmd) < 0)
			exit (1);
		dup_redirect(cmd);
		if (cmd->simple_command && cmd->simple_command[0])
		{
			ft_printf_fd(2, "Executando: %s\n", cmd->simple_command[0]);
			execvp(cmd->simple_command[0], cmd->simple_command);
		}
		ft_printf_fd(2, "minishell: Erro ao executar o comando: %s\n", cmd->simple_command[0]);
		exit(1);
	}
	else
	{
		wait(NULL);
		clean_heredoc(cmd);
	}
}*/

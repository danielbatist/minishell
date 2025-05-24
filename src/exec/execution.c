/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/24 18:20:08 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_command(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (open_redirect(cmd) < 0)
			exit (1);
		dups_redirect(cmd);
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
}

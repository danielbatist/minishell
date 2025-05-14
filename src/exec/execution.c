/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/14 18:25:32 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_command(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (apply_redirect(cmd) < 0)
			exit (1);
		if (cmd->simple_command && cmd->simple_command[0])
		{
			execvp(cmd->simple_command[0], cmd->simple_command);
			printf("Executando: %s\n", cmd->simple_command[0]);
		}
		ft_printf_fd(2, "minishell: Erro ao executar o comando: %s\n", cmd->simple_command[0]);
		exit(1);
	}
	else
		wait(NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:36:25 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/03 13:47:20 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtins(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	exec_builtins(t_command *cmd)
{
	char	**args;

	args = cmd->simple_command;
	if (!args || !args[0])
		return (0);
	if (!ft_strcmp(args[0], "cd"))
	 	return (ft_cd(cmd->simple_command, cmd->env_list));
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(cmd->simple_command));
	if (!ft_strcmp(args[0], "pwd"))
	 	return (ft_pwd());
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(cmd->simple_command, cmd->env_list));
	if (!ft_strcmp(args[0], "env"))
		return (ft_env(cmd->env_list));
	/*if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(cmd));
	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(cmd));*/
	return (0);
}

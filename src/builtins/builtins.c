/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:36:25 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/02 19:07:43 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtins(const char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 \
			|| ft_strcmp(cmd, "pwd") == 0 \
			|| ft_strcmp(cmd, "export") == 0 \
			|| ft_strcmp(cmd, "unset") == 0 \
			|| ft_strcmp(cmd, "env") == 0 \
			|| ft_strcmp(cmd, "exit") == 0);
}

/*int	exec_builtins(t_list *token, t_env **envp)
{
	char	*cmd;

	cmd = ((t_token *)token->content)->lexeme;
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(token));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(token, envp));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(token, envp));
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(token, envp));
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(envp));
	if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(token));
	return (0);
}*/

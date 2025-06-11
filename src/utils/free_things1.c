/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:02:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 17:59:56 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_scanner(t_scanner *scanner)
{
	if (!scanner)
		return ;
	if (scanner->tokens)
		ft_lstclear(&scanner->tokens, free_token);
	free(scanner);
}

t_command	*free_and_return(t_scanner *scanner)
{
	if (scanner)
		free_scanner(scanner);
	return (NULL);
}

void	free_pipes(t_pipefd *pipefd, int n_of_pipes)
{
	int	i;

	if (!pipefd)
		return ;
	i = 0;
	while (i < n_of_pipes)
	{
		close(pipefd[i].fd[0]);
		close(pipefd[i].fd[1]);
		i++;
	}
	free(pipefd);
}

void	free_exec(char **exec)
{
	int	i;

	if (!exec)
		return ;
	i = 0;
	while (exec[i])
		free(exec[i++]);
	free(exec);
}

void	free_child_not_found(char *path, char **envp, t_command *cmd, int *i)
{
	ft_printf_fd(2, "%s: command not found\n", cmd[*i].simple_command[0]);
	free_exec(envp);
	free(path);
	free_env_list(cmd->env_list);
	free(cmd->data->pids);
	free(cmd->data);
	free_complex_command(cmd);
	exit(127);
}

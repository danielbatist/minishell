/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:02:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/29 15:33:20 by dbatista         ###   ########.fr       */
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

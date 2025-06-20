/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:24:25 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 20:24:41 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_number_of_pipes(t_command *complex_command)
{
	int	i;

	i = 0;
	while (complex_command[i].simple_command)
		i++;
	return (--i);
}

int	get_pipefd(t_command *complex_command, t_pipefd **pipefd)
{
	int	n_of_pipes;
	int	i;

	n_of_pipes = get_number_of_pipes(complex_command);
	if (n_of_pipes < 1)
		return (0);
	*pipefd = (t_pipefd *)malloc(sizeof(t_pipefd) * n_of_pipes);
	if (!(*pipefd))
		return (-1);
	i = 0;
	while (i < n_of_pipes)
	{
		pipe((*pipefd)[i].fd);
		i++;
	}
	return (n_of_pipes);
}

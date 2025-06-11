/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:36:43 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 18:06:07 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_exit_status(int status)
{
	*get_exit_status() = (unsigned char)status;
}

int	*get_exit_status(void)
{
	static int	status = 0;

	return (&status);
}

int	check_error_flag(t_command *cmd, int *i)
{
	if (cmd[*i].error_flag)
	{
		clean_heredoc(&cmd[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}

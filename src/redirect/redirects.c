/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:22:24 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/09 22:01:53 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dup2_redirect(t_command *cmd)
{
	if (cmd->fd_in > 0 && cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 0 && cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

int	handle_in(t_command *cmd)
{
	int	fd;

	if (cmd->heredoc_file)
	{
		fd = open_herefile(cmd->heredoc_file);
		if (fd < 0)
			return (-1);
		cmd->fd_in = fd;
	}
	else if (cmd->infile)
	{
		fd = open_infile(cmd->infile);
		if (fd < 0)
			return (-1);
		cmd->fd_in = fd;
	}
	return (0);
}

int	handle_out(t_command *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		fd = open_outfile(cmd->outfile);
		if (fd < 0)
			return (-1);
		cmd->fd_out = fd;
	}
	else if (cmd->append_file)
	{
		fd = open_append(cmd->append_file);
		if (fd < 0)
			return (-1);
		cmd->fd_out = fd;
	}
	return (0);
}

int	open_redirect(t_command *cmd)
{
	if (handle_in(cmd) < 0)
		return (-1);
	if (handle_out(cmd) < 0)
		return (-1);
	return (0);
}

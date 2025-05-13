/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:22:24 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/13 20:18:59 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror(infile);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 outfile");
		close(fd);
		return (-1);
	}
	if (fd != STDOUT_FILENO)
		close(fd);
	return (fd);
}

static int	open_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(outfile);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 outfile");
		close(fd);
		return (-1);
	}
	if (fd != STDOUT_FILENO)
		close(fd);
	return (fd);
}

static int	open_append(char *append)
{
	int	fd;

	fd = open(append, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(append);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 outfile");
		close(fd);
		return (-1);
	}
	if (fd != STDOUT_FILENO)
		close(fd);
	return (fd);
}

int	apply_redirect(t_command *cmd)
{
	int	fd;

	if (cmd->infile && open_infile(cmd->infile) < 0)
		return (-1);
	if (cmd->outfile && open_outfile(cmd->outfile) < 0)
		return (-1);
	if (cmd->append_file && open_append(cmd->append_file) < 0)
		return (-1);
	return (0);
}

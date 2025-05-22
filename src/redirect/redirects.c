/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:22:24 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/21 11:07:06 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_execution(t_command *cmd)
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

int	open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error ao abrir arquivo de entrada: %s\n", infile);
		return (-1);
	}
	return (fd);
}

int	open_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error ao abrir arquivo de saida: %s\n", outfile);
		return (-1);
	}
	return (fd);
}

int	open_append(char *append)
{
	int	fd;

	fd = open(append, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error ao abrir arquivo em modo append: %s\n", append);
		return (-1);
	}
	return (fd);
}

int	apply_redirect(t_command *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		printf("Redirecionando entrada para: %s\n", cmd->infile);
		fd = open_infile(cmd->infile);
		if (fd < 0)
			return (-1);
		cmd->fd_in = fd;
	}
	if (cmd->outfile)
	{
		printf("Redirecionando saida para: %s\n", cmd->outfile);
		fd = open_outfile(cmd->outfile);
		if (fd < 0)
			return (-1);
		cmd->fd_out =fd;
	}
	if (cmd->append_file)
	{
		printf("Acrescentando saida em: %s\n", cmd->append_file);
		fd = open_append(cmd->append_file);
		if (fd < 0)
			return (-1);
		cmd->fd_out = fd;
	}
	if (cmd->heredoc_file) // Corrigir para usar heredoc_file
	{
		printf("Redirecionando para o Heredoc: %s\n", cmd->heredoc_file);
		fd = open_infile(cmd->heredoc_file);
		if (fd < 0)
			return (-1);
		cmd->fd_in = fd;
	}
	return (0);
}

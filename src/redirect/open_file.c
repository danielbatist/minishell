/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:14:49 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/24 18:18:38 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_herefile(char *heredoc)
{
	int	fd;

	fd = open(heredoc, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error ao abrir arquivo de entrada: %s\n", heredoc);
		return (-1);
	}
	return (fd);
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

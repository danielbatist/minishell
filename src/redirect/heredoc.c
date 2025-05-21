/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:44:50 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/20 22:17:54 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	clean_heredoc(t_command *cmd)
{
	if (cmd->infile)
	{
		unlink(cmd->infile);
		free(cmd->infile);
		cmd->infile = NULL;
	}
}


char	*create_tmp_file(void)
{
	static int		index = 0;
	char			*filename;
	char			*idx_str;

	idx_str = ft_itoa(index++);
	filename = ft_strjoin("/tmp/.heredoc_tmp", idx_str);
	free(idx_str);
	return (filename);
}

int	open_heredoc(t_command *cmd, char *delim)
{
	int		fd;
	char	*filename;
	char	*line;

	filename = create_tmp_file();
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_printf_fd(2, "Erro na abertura de arquivo temporario do heredoc");
		free(filename);
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf_fd(2, "minishell: heredoc finalizado por fim de arquivo.\n");
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	cmd->infile = filename;
	return (0);
}

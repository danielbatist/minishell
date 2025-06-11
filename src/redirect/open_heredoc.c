/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:00:22 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 11:30:41 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_warning(char *delim)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_printf_fd(2, "bash: warning: here-document at line 1 ");
	ft_printf_fd(2, "delimited by end-of-file (wanted `%s')\n", delim);
}

static int	process_heredoc_line(int fd, t_command *cmd,
		char *line)
{
	char	*expanded;

	if (cmd->heredoc_quoted == FALSE)
	{
		expanded = here_exp(line, cmd->env_list);
		free(line);
		if (!expanded)
			return (1);
		line = expanded;
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (0);
}

static int	read_heredoc_loop(int fd, t_command *cmd,
		char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_warning(delim);
			return (0);
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			return (0);
		}
		if (process_heredoc_line(fd, cmd, line))
			return (1);
	}
	return (0);
}

int	open_heredoc(t_command *cmd, char *delim,
		char *tmp_filename)
{
	int		fd;

	fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error creating heredoc\n");
		free(tmp_filename);
		return (1);
	}
	if (read_heredoc_loop(fd, cmd, delim))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

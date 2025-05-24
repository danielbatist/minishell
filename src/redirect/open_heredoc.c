/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:00:22 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/24 19:16:05 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	write_line_to_fd(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (0);
}

static void	print_warning(char *delim)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_printf_fd(2, "bash: warning: here-document at line 1 delimited by end-of-file\
			(wanted `%s')\n", delim);
}

static char	*expand_if_needed(t_command *cmd, char *line, t_list *env_list)
{
	char	*expanded;

	if (cmd->heredoc_quoted == FALSE)
	{
		expanded = here_exp(line, env_list);
		free(line);
		if (!expanded)
			return (NULL);
		line = expanded;
	}
	return (line);
}




int	open_heredoc(t_command *cmd, char *delim, char *tmp_filename, t_list *env_list)
{
	int		fd;
	char	*line;

	fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error open heredoc\n");
		free(tmp_filename);
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_warning(delim);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		line = expand_if_needed(cmd, line, env_list);
		if (!line)
		{
			close(fd);
			return (1);
		}
		write_line_to_fd(fd, line);
		free(line);
	}
	close(fd);
	return (0);
}

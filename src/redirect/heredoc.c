/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:44:50 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 01:08:45 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_heredoc_delimiter(t_command *cmd, t_token *token)
{
	cmd->heredoc_quoted = (token->type == SINGLE_QUOTED
			|| token->type == DOUBLE_QUOTED);
	if (cmd->heredoc_quoted)
		return (ft_strtrim(token->lexeme, "\"\'"));
	else
		return (ft_strdup(token->lexeme));
}

static int	handle_heredoc_child(t_command *cmd, char *delim,
		char *tmp_filename, t_scanner *scanner)
{
	int	error_heredoc;
	int	i;

	i = 0;
	signal(SIGINT, SIG_DFL);
	error_heredoc = open_heredoc(cmd, delim, tmp_filename);
	free_env_list(cmd->env_list);
	free(tmp_filename);
	while (cmd->simple_command[i])
	{
		free(cmd->simple_command[i++]);
	}
	free(cmd->simple_command);
	free(cmd);
	free_scanner(scanner);
	if (error_heredoc)
		exit(1);
	free(delim);
	exit(0);
}

static int	handle_heredoc_parent(pid_t pid, char *tmp_filename,
		char **out_file)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		unlink(tmp_filename);
		free(tmp_filename);
		*out_file = NULL;
		set_exit_status(130);
		return (1);
	}
	if (WEXITSTATUS(status) != 0)
	{
		unlink(tmp_filename);
		free(tmp_filename);
		*out_file = NULL;
		return (1);
	}
	*out_file = tmp_filename;
	return (0);
}

int	handle_heredoc(t_command *cmd, char **out_file,
		t_token *next, t_scanner *scanner)
{
	pid_t	pid;
	char	*delim;
	char	*tmp_filename;

	tmp_filename = create_tmp_file();
	if (!tmp_filename)
		return (1);
	delim = get_heredoc_delimiter(cmd, next);
	if (!delim)
	{
		free(tmp_filename);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(delim);
		return (1);
	}
	if (pid == 0)
		handle_heredoc_child(cmd, delim, tmp_filename, scanner);
	free(delim);
	return (handle_heredoc_parent(pid, tmp_filename, out_file));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:44:50 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/24 11:37:29 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*here_exp(char *line, t_list *env_list)
{
	t_token		*token;
	t_list		*list;
	t_scanner	scanner;
	char		*new_line;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexeme = ft_strdup(line);
	token->type = TARGET;
	list = ft_lstnew(token);
	scanner.tokens = list;
	env_expansion(env_list, &scanner);
	new_line = ft_strdup(token->lexeme);
	ft_lstdelone(list, free_token);
	return (new_line);
}

void	clean_heredoc(t_command *cmd)
{
	if (cmd->infile && cmd->is_heredoc)
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

int	handle_heredoc(t_command *cmd, char **out_file, t_token *next, t_list *env_list)
{
	pid_t	pid;
	int		status;
	char	*delim;
	char	*tmp_filename;

	tmp_filename = create_tmp_file();
	if (!tmp_filename)
		return (1);
	if (next->type == SINGLE_QUOTED || next->type == DOUBLE_QUOTED)
	{
		cmd->heredoc_quoted = TRUE;
		delim = ft_strtrim(next->lexeme, "\"\'");
	}
	else
	{
		cmd->heredoc_quoted = FALSE;
		delim = ft_strdup(next->lexeme);
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
	{
		signal(SIGINT, SIG_DFL);
		if (open_heredoc(cmd, delim, tmp_filename, env_list))
			exit(1);
		free(delim);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(delim);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			unlink(tmp_filename);
			free(tmp_filename);
			*out_file = NULL;
			ft_printf_fd(2, "minishell: heredoc finalizado por sinal.\n");
			return (130);
		}
		if (WEXITSTATUS(status) != 0)
		{
			unlink(tmp_filename);
			free(tmp_filename);
			*out_file = NULL;
			ft_printf_fd(2, "minishell: erro ao criar o heredoc.\n");
			return (1);
		}
		*out_file = tmp_filename;
		cmd->is_heredoc = TRUE;
	}
	return (0);
}

int	open_heredoc(t_command *cmd, char *delim, char *tmp_filename, t_list *env_list)
{
	int		fd;
	char	*line;
	char	*expanded;

	fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_printf_fd(2, "Erro na abertura de arquivo temporario do heredoc");
		free(tmp_filename);
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			ft_printf_fd(2, "bash: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", delim);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (cmd->heredoc_quoted == FALSE)
		{
			expanded = here_exp(line, env_list);
			free(line);
			if (!expanded)
			{
				close(fd);
				return (1);
			}
			line = expanded;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:44:50 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/22 10:16:49 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

char	*here_exp(char *line, t_list *env_list, t_command *cmd)
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
	env_expansion(env_list, &scanner, cmd);
	new_line = ft_strdup(token->lexeme);
	free(token->lexeme);
	free(token);
	ft_lstdelone(list, free_token);
	return (new_line);
}

int	handle_heredoc(t_command *cmd, char **out_file, char *lexeme, t_list *env_list)
{
	int		fd;
	char	*filename;

	if (lexeme[0] == '\'' || lexeme[0] == '\"')
	{
		cmd->heredoc_quoted = TRUE;
		filename = ft_strtrim(lexeme, "\"\'");
	}
	else
	{
		cmd->heredoc_quoted = FALSE;
		filename = ft_strdup(lexeme);
	}
	fd = open_heredoc(cmd, filename, env_list);
	if (fd < 0)
	{
		ft_printf_fd(2, "Error");
		free(filename);
		return (1);
	}
	*out_file = filename;
	return (0);
}

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

int	open_heredoc(t_command *cmd, char *delim, t_list *env_list)
{
	int		fd;
	char	*filename;
	char	*line;
	char	*expanded;

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
		{
			free(line);
			break ;
		}
		if (cmd->heredoc_quoted == FALSE)
		{
			expanded = here_exp(line, env_list, cmd);
			free(line);
			line = expanded;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_file = filename;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:08 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/10 19:19:21 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	clear_conflict_redirects(t_command *cmd, t_token_type type)
{
	if (type == REDIRECT_OUT)
	{
		free(cmd->append_file);
		cmd->append_file = NULL;
	}
	else if (type == APPEND)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
}

static void	set_redirect(t_token *token, t_command *cmd, char *filename)
{
	if (!filename)
		return ;
	clear_conflict_redirects(cmd, token->type);
	if (token->type == REDIRECT_IN)
	{
		free(cmd->infile);
		cmd->infile = filename;
	}
	else if (token->type == REDIRECT_OUT)
	{
		free(cmd->outfile);
		cmd->outfile = filename;
	}
	else if (token->type == APPEND)
	{
		free(cmd->append_file);
		cmd->append_file = filename;
	}
	else if (token->type == HEREDOC)
	{
		free(cmd->heredoc_file);
		cmd->heredoc_file = filename;
	}
}

int	handle_redirect_file(t_token *token, t_token *next_token, t_command *cmd)
{
	char	*filename;
	int		fd;

	filename = ft_strdup(next_token->lexeme);
	if (!filename)
		return (1);
	if (token->type == REDIRECT_OUT)
		fd = open_outfile(filename);
	else if (token->type == REDIRECT_IN)
		fd = open_infile(filename);
	else if (token->type == APPEND)
		fd = open_append(filename);
	else
		fd = -1;
	if (fd < 0)
	{
		ft_printf_fd(2, "Error open file %s\n", filename);
		free(filename);
		return (1);
	}
	close(fd);
	set_redirect(token, cmd, filename);
	return (0);
}

int	handle_redirect_heredoc(t_token *token, t_token *next_token,
	t_command *cmd, t_list *env_list)
{
	char	*filename;

	if (!next_token || !next_token->lexeme)
		return (1);
	if (handle_heredoc(cmd, &filename, next_token, env_list))
		return (1);
	set_redirect(token, cmd, filename);
	return (0);
}

int	handle_redirects(t_list *start, t_command *cmd, t_list *env_list)
{
	t_token	*token;
	t_token	*next_token;

	while (start && ((t_token *)start->content)->type != PIPE)
	{
		token = (t_token *)start->content;
		if (is_redirect(token->type) && start->next)
		{
			start = start->next;
			next_token = (t_token *)start->content;
			if (token->type == HEREDOC)
			{	
				if (handle_redirect_heredoc(token, next_token, cmd, env_list))
					return (1);
			}
			else if (handle_redirect_file(token, next_token, cmd))
				return (1);
		}
		start = start->next;
	}
	return (0);
}

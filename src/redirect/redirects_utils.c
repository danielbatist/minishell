/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:08 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/22 21:37:35 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirects_token(t_list **token_list)
{
	*token_list = (*token_list)->next;
	if (*token_list)
		*token_list = (*token_list)->next;
}

static void	set_redirect(t_token *token, t_command *cmd, char *filename)
{
	if (!filename)
		return ;
	if (token->type == REDIRECT_IN)
	{
		free(cmd->infile);
		cmd->infile = filename;
	}
	else if (token->type == REDIRECT_OUT)
	{
		free(cmd->append_file);
		cmd->append_file = NULL;
		free(cmd->outfile);
		cmd->outfile = filename;
	}
	else if (token->type == APPEND)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
		free(cmd->append_file);
		cmd->append_file = filename;
	}
	else if (token->type == HEREDOC)
	{
		free(cmd->heredoc_file);
		cmd->heredoc_file = filename;
	}
}

int	handle_redirects(t_list *start, t_command *cmd, t_list *env_list)
{
	t_token	*token;
	t_token	*next_token;
	char	*filename;
	int		fd;

	while (start && ((t_token *)start->content)->type != PIPE)
	{
		token = (t_token *)start->content;
		if (is_redirect(token->type) && start->next)
		{
			printf("Redirects: %s (%u)\n", token->lexeme, token->type);
			start = start->next;
			next_token = (t_token *)start->content;
			if (!next_token || !next_token->lexeme)
				return (print_error(next_token));
			if (token->type == HEREDOC)
			{
				handle_heredoc(cmd, &filename, next_token->lexeme, env_list);
				set_redirect(token, cmd, filename);
				return (1);
			}
			filename = ft_strdup(next_token->lexeme);
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
				ft_printf_fd(2, "Error\n");
				free(filename);
				return (1);
			}
			close(fd);
			set_redirect(token, cmd, filename);
		}
		start = start->next;
	}
	return (0);
}

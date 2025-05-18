/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:08 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/18 18:55:57 by dbatista         ###   ########.fr       */
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
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = filename;
	}
}

int	handle_redirects(t_list *start, t_command *cmd)
{
	t_token	*token;
	t_token	*next_token;
	char	*filename;

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
			filename = ft_strdup(next_token->lexeme);
			set_redirect(token, cmd, filename);
		}
		start = start->next;
	}
	return (0);
}

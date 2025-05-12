/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:22:24 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/12 20:34:22 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_redirect(t_token *token, t_command *cmd, char *filename)
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
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = filename;
	}
}

void	handle_redirects(t_list *start, t_command *cmd)
{
	t_token	*token;
	char	*filename;

	while (start && ((t_token *)start->content)->type != PIPE)
	{
		token = (t_token *)start->content;
		if (is_redirect(token->type) && start->next)
		{
			printf("Redirects: %s (%u)\n", token->lexeme, token->type);
			start = start->next;
			filename = ft_strdup(((t_token *)start->content)->lexeme);
			set_redirect(token, cmd, filename);
		}
		start = start->next;
	}
}


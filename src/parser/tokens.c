/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:37:00 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/23 18:04:14 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_plus(t_token *token, char c, t_token_type token_type)
{
	if (token_type == EOF_TOKEN || token_type == PIPE
		|| token_type == REDIRECT_IN || token_type == REDIRECT_OUT
		|| token_type == APPEND || token_type == HEREDOC
		|| token_type == UNCLOSED)
	{
		token->plus = FALSE;
		return ;
	}
	if (c != '\0' && c != ' ' && c != '\t' && c != '\n'
		&& c != '|' && c != '>' && c != '<')
		token->plus = TRUE;
	else
		token->plus = FALSE;
}

void	add_token(t_scanner *scanner, t_token_type token_type)
{
	int		len;
	t_token	*token;
	t_list	*token_node;

	len = scanner->current - scanner->start;
	if (len <= 0)
		return ;
	token = malloc(sizeof(t_token));
	token->lexeme = ft_substr(scanner->src, scanner->start, scanner->current
			- scanner->start);
	token->type = token_type;
	if (is_redirect(token_type))
		scanner->is_command = REDIRECT;
	set_plus(token, scanner->src[scanner->current], token_type);
	if ((scanner->start > 0) && (scanner->src[scanner->start - 1] == ' '
			|| scanner->src[scanner->start - 1] == '\t'
			|| scanner->src[scanner->start - 1] == '\n'))
		token->has_space = TRUE;
	else
		token->has_space = FALSE;
	if (token_type == DOUBLE_QUOTED || token_type == SINGLE_QUOTED)
		token->has_space = FALSE;
	token_node = ft_lstnew(token);
	ft_lstadd_back(&scanner->tokens, token_node);
}

void	add_str_token(t_scanner *scanner, t_token_type token_type)
{
	char	quote;

	if (token_type == DOUBLE_QUOTED)
		quote = '\"';
	else if (token_type == SINGLE_QUOTED)
		quote = '\'';
	else
		return ;
	scanner->start = scanner->current;
	while (scanner->src[scanner->current]
		&& scanner->src[scanner->current] != quote)
		scanner->current++;
	if (scanner->src[scanner->current] == quote)
	{
		add_token(scanner, token_type);
		scanner->current++;
		scanner->start = scanner->current;
	}
	else
	{
		scanner->start--;
		while (scanner->src[scanner->current])
			scanner->current++;
		add_token(scanner, UNCLOSED);
	}
}

void	add_multichar_token(t_scanner *scanner, t_token_type token_type)
{
	if (token_type == TARGET)
		scanner->is_command = TRUE;
	else if (token_type == COMMAND)
		scanner->is_command = FALSE;
	if (token_type == APPEND || token_type == HEREDOC)
	{
		scanner->is_command = REDIRECT;
		scanner->current++;
	}
	else
	{
		while (scanner->src[scanner->current]
			&& scanner->src[scanner->current] != ' '
			&& scanner->src[scanner->current] != '|'
			&& scanner->src[scanner->current] != '\"'
			&& scanner->src[scanner->current] != '\''
			&& scanner->src[scanner->current] != '>'
			&& scanner->src[scanner->current] != '<')
			scanner->current++;
	}
	add_token(scanner, token_type);
}

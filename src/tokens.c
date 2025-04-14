/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:37:00 by eteofilo          #+#    #+#             */
/*   Updated: 2025/04/14 15:22:15 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_token(t_scanner *scanner, t_token_type token_type)
{
	t_token	*token;
	t_list	*token_node;

	if (token_type == PIPE)
		scanner->is_command = TRUE;
	if (token_type == REDIRECT_IN || token_type == REDIRECT_OUT)
		scanner->is_command = REDIRECT;
	token = malloc(sizeof(t_token));
	token->lexeme = ft_substr(scanner->src, scanner->start, scanner->current
			- scanner->start);
	token->type = token_type;
	token_node = ft_lstnew(token);
	ft_lstadd_back(&scanner->tokens, token_node);
	if ((token_type == REDIRECT_OUT && scanner->src[scanner->current] == '|')
		|| token_type == DOUBLE_QUOTED || token_type == SINGLE_QUOTED)
		scanner->current++;
}

void	add_str_token(t_scanner *scanner, t_token_type token_type)
{
	while (scanner->src[scanner->current]
		&& scanner->src[scanner->current] != (char)token_type)
		scanner->current++;
	if (scanner->src[scanner->current] == (char)token_type)
	{
		scanner->start++;
		if ((char)token_type == '\"')
			add_token(scanner, DOUBLE_QUOTED);
		if ((char)token_type == '\'')
			add_token(scanner, SINGLE_QUOTED);
	}
	else
		add_token(scanner, UNCLOSED);
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

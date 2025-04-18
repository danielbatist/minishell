/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:04:56 by eteofilo          #+#    #+#             */
/*   Updated: 2025/04/18 06:14:50 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_at_end(t_scanner *scanner)
{
	if (scanner->src[scanner->current] == '\0')
		return (1);
	return (0);
}

static void	scan_token(t_scanner *scanner)
{
	char	*s;

	s = scanner->src + scanner->current++;
	if (*s == '|')
		add_token(scanner, PIPE);
	else if (s[0] == '>' && s[1] == '>')
		add_multichar_token(scanner, APPEND);
	else if (s[0] == '<' && s[1] == '<')
		add_multichar_token(scanner, HEREDOC);
	else if (*s == '>')
		add_token(scanner, REDIRECT_OUT);
	else if (*s == '<')
		add_token(scanner, REDIRECT_IN);
	else if (*s == '\"')
		add_str_token(scanner, DOUBLE_QUOTED);
	else if (*s == '\'')
		add_str_token(scanner, SINGLE_QUOTED);
	else if (scanner->is_command == TRUE && *s != ' ')
		add_multichar_token(scanner, COMMAND);
	else if (scanner->is_command == REDIRECT && *s != ' ')
		add_multichar_token(scanner, TARGET);
	else if (*s == '-')
		add_multichar_token(scanner, FLAG);
	else if (*s != ' ')
		add_multichar_token(scanner, PARAMETER);
}

void	scan_tokens(t_scanner *scanner)
{
	t_token	*eof;

	eof = malloc(sizeof(t_token));
	if (!eof)
		return ;
	while (!is_at_end(scanner))
	{
		scanner->start = scanner->current;
		scan_token(scanner);
	}
	eof->type = EOF;
	eof->lexeme = strdup("");
	ft_lstadd_back(&scanner->tokens, ft_lstnew(eof));
}

t_scanner	*init_scanner(char *input)
{
	t_scanner	*scanner;

	scanner = malloc(sizeof(t_scanner));
	scanner->current = 0;
	scanner->line = 1;
	scanner->is_command = TRUE;
	scanner->start = 0;
	scanner->src = input;
	scanner->tokens = NULL;
	return (scanner);
}

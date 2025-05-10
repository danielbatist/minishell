/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:04:56 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/10 19:01:00 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_special_token(t_scanner *scanner, char *s)
{
	if (*s == '|')
		add_token(scanner, PIPE);
	else if (*s == '>' && scanner->src[scanner->current] == '>')
		add_multichar_token(scanner, APPEND);
	else if (*s == '<' && scanner->src[scanner->current] == '<')
		add_multichar_token(scanner, HEREDOC);
	else if (*s == '>')
		add_token(scanner, REDIRECT_OUT);
	else if (*s == '<')
		add_token(scanner, REDIRECT_IN);
	else if (*s == '\"')
		add_str_token(scanner, DOUBLE_QUOTED);
	else if (*s == '\'')
		add_str_token(scanner, SINGLE_QUOTED);
}

static void	handle_general_token(t_scanner *scanner, char *s)
{
	if (is_flag(scanner, s))
		add_multichar_token(scanner, FLAG);
	else if (scanner->is_command == TRUE)
	{
		add_multichar_token(scanner, COMMAND);
		scanner->is_command = FALSE;
	}
	else if (scanner->is_command == REDIRECT)
		add_multichar_token(scanner, TARGET);
	else
		add_multichar_token(scanner, PARAMETER);
}

static void	scan_token(t_scanner *scanner)
{
	char	*s;

	s = scanner->src + scanner->current++;
	if (*s == ' ')
	{
		scanner->start = scanner->current;
		return ;
	}
	if (ft_strchr("|<>\"\'", *s))
		handle_special_token(scanner, s);
	else
		handle_general_token(scanner, s);
}

void	scan_tokens(t_scanner *scanner)
{
	t_token	*eof;

	eof = malloc(sizeof(t_token));
	if (!eof)
		return ;
	while (scanner->src[scanner->current])
	{
		scanner->start = scanner->current;
		scan_token(scanner);
	}
	eof->type = EOF_TOKEN;
	eof->lexeme = strdup("");
	eof->plus = FALSE;
	ft_lstadd_back(&scanner->tokens, ft_lstnew(eof));
}

t_scanner	*init_scanner(char *input)
{
	t_scanner	*scanner;

	scanner = malloc(sizeof(t_scanner));
	if (!scanner)
		return (NULL);
	scanner->current = 0;
	scanner->is_command = TRUE;
	scanner->start = 0;
	scanner->src = input;
	scanner->tokens = NULL;
	return (scanner);
}

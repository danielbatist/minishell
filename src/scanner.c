/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:04:56 by eteofilo          #+#    #+#             */
/*   Updated: 2025/04/11 15:16:11 by eteofilo         ###   ########.fr       */
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
	token->lexeme = ft_substr(scanner->src, scanner->start, scanner->current - scanner->start);
	token->type = token_type;
	token_node = ft_lstnew(token);
	ft_lstadd_back(&scanner->tokens, token_node);
}

void	add_str_token(t_scanner *scanner, t_token_type token_type)
{
	while (scanner->src[scanner->current]
		&& scanner->src[scanner->current] != (char)token_type)
		scanner->current++;
	if (scanner->src[scanner->current] == (char)token_type)
	{
		scanner->current++;
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
			&& scanner->src[scanner->current] != ' ')
			scanner->current++;
	}

	add_token(scanner, token_type);
}

static int	is_at_end(t_scanner *scanner)
{
	if (scanner->src[scanner->current] == '\0')
		return (1);
	return (0);
}

static void scan_token(t_scanner *scanner)
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
	else if (scanner->is_command == TRUE  && *s != ' ')
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
	scanner->line = 0;
	scanner->is_command = TRUE;
	scanner->start = 0;
	scanner->src = input;
	scanner->tokens = NULL;
	return (scanner);
}

int	main(void)
{
	char	*input;
	t_scanner	*scanner;
	//char	*token_clean;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("\nSaindo do minishell...\n");
			break ;
		}
		if (*input)
			add_history(input);
		scanner = init_scanner(input);
		scan_tokens(scanner);
		while (scanner->tokens)
		{
			if (((t_token *)(scanner->tokens->content))->type == COMMAND)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "COMMAND");
			if (((t_token *)(scanner->tokens->content))->type == PARAMETER)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "PARAMETER");
			if (((t_token *)(scanner->tokens->content))->type == FLAG)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "FLAG");
			if (((t_token *)(scanner->tokens->content))->type == PIPE)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "PIPE");
			if (((t_token *)(scanner->tokens->content))->type == REDIRECT_IN)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "REDIRECT_IN");
			if (((t_token *)(scanner->tokens->content))->type == REDIRECT_OUT)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "REDIRECT_OUT");
			if (((t_token *)(scanner->tokens->content))->type == HEREDOC)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "HEREDOC");
			if (((t_token *)(scanner->tokens->content))->type == APPEND)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "APPEND");
			if (((t_token *)(scanner->tokens->content))->type == TARGET)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "TARGET");
			if (((t_token *)(scanner->tokens->content))->type == SINGLE_QUOTED)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "SINGLE_QUOTED");
			if (((t_token *)(scanner->tokens->content))->type == DOUBLE_QUOTED)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "DOUBLE_QUOTED");
			if (((t_token *)(scanner->tokens->content))->type == UNCLOSED)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "UNCLOSED");
			if (((t_token *)(scanner->tokens->content))->type == EOF_TOKEN)
				printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "EOF_TOKEN");
			scanner->tokens = scanner->tokens->next;
		}
		free(input);
	}
	return (0);
}

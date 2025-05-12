/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:21:12 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/12 19:57:38 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_quotes(t_list *tokens)
{
	t_token	*token;

	if (!tokens)
		return (0);
	while (tokens)
	{
		token = tokens->content;
		if (token->type == UNCLOSED)
		{
			print_error(token);
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	handle_pipe(t_list *tokens)
{
	t_token	*token;
	t_token	*next;

	if (!tokens)
		return (0);
	token = tokens->content;
	if (token->type == PIPE)
		return (print_error(token));
	while (tokens && tokens->next)
	{
		token = tokens->content;
		next = tokens->next->content;
		if (token->type == PIPE && next->type == PIPE)
			return (print_error(token));
		tokens = tokens->next;
	}
	if (token && token->type == PIPE)
		return (print_error(token));
	return (0);
}

int	handle_redirect(t_list *tokens)
{
	t_token	*token;
	t_token	*next;

	while (tokens)
	{
		token = tokens->content;
		next = NULL;
		if (tokens->next)
			next = tokens->next->content;
		if (is_redirect(token->type) && (!next || next->type == EOF_TOKEN))
			return (print_error(token));
		if (next)
		{
			if (check_redirect_in(token, next))
				return (1);
			if (check_redirect_out(token, next))
				return (1);
			if (check_redirects(token, next))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	handle_error(t_list *tokens)
{
	if (handle_quotes(tokens))
		return (1);
	if (handle_pipe(tokens))
		return (1);
	if (handle_redirect(tokens))
		return (1);
	return (0);
}

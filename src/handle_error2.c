/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:21:12 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/18 01:24:27 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_pipe(t_list *tokens)
{
	t_token	*token;
	t_token	*next;

	if (!tokens)
		return (0);
	token = tokens->content;
	if (token->type == PIPE)
		return (print_error(token->lexeme[0]));
	while (tokens && tokens->next)
	{
		token = tokens->content;
		next = tokens->next->content;
		if (token->type == PIPE && next->type == PIPE)
			return (print_error(token->lexeme[0]));
		tokens = tokens->next;
	}
	if (token && token->type == PIPE)
		return (print_error(token->lexeme[0]));
	return (0);
}

int	handle_error(t_list *tokens)
{
	if (handle_pipe(tokens))
		return (1);
	if (handle_redirect(tokens))
		return (1);
	return (0);
}

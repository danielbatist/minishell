/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:20:21 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 20:05:11 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_redirect_in(t_token *token, t_token *next)
{
	if ((token->type == REDIRECT_IN && next->type == REDIRECT_IN) \
		|| (token->type == REDIRECT_IN && next->type == PIPE))
		return (print_error(next));
	if (token->type == REDIRECT_IN && next->type == TARGET)
	{
		if (access(next->lexeme, F_OK) != 0)
		{
			print_error(next);
			return (1);
		}
	}
	return (0);
}

int	check_redirect_out(t_token *token, t_token *next)
{
	int	fd;

	if (token->type == REDIRECT_OUT && next->type == TARGET)
	{
		if (access(next->lexeme, F_OK) != 0)
		{
			fd = open(next->lexeme, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				return (1);
			}
			close(fd);
		}
	}
	return (0);
}

int	check_redirect_end(t_token *last, t_list *tokens)
{
	if (last && (last->type == REDIRECT_IN || last->type == REDIRECT_OUT \
	|| last->type == APPEND || last->type == HEREDOC))
		return (print_error((t_token *)tokens->content));
	return (0);
}

static int	is_redirect(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT \
	|| type == APPEND || type == HEREDOC);
}

int	check_redirects(t_token *token, t_token *next)
{
	if (is_redirect(token->type) && is_redirect(next->type))
		return (print_error(next));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:20:21 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/18 06:06:02 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_redirect_in(t_token *token, t_token *next)
{
	if ((token->type == REDIRECT_IN && next->type == REDIRECT_IN) \
		|| (token->type == REDIRECT_IN && next->type == PIPE))
		return (print_error(next->lexeme[0]));
	if (token->type == REDIRECT_IN && next->type == TARGET)
	{
		if (access(next->lexeme, F_OK) != 0)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(next->lexeme, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_redirect_out(t_token *token, t_token *next)
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

static int	check_redirects(t_token *token, t_token *next)
{
	if ((token->type == REDIRECT_IN && next->type == REDIRECT_IN) \
	|| (token->type == REDIRECT_OUT && next->type == REDIRECT_OUT) \
	|| (token->type == APPEND && next->type == REDIRECT_IN) \
	|| (token->type == HEREDOC && next->type == REDIRECT_OUT))
		return (print_error(next->lexeme[0]));
	return (0);
}

static int	check_redirect_end(t_token *token)
{
	if (token && (token->type == REDIRECT_IN || token->type == REDIRECT_OUT \
	|| token->type == APPEND || token->type == HEREDOC))
		return (print_error(' '));
	return (0);
}

int	handle_redirect(t_list *tokens)
{
	t_token	*token;
	t_token	*next;

	if (!tokens || !tokens->next)
		return (0);
	while (tokens && tokens->next)
	{
		token = tokens->content;
		next = tokens->next->content;
		if (check_redirect_in(token, next))
			return (1);
		if (check_redirect_out(token, next))
			return (1);
		if (check_redirects(token, next))
			return (1);
		tokens = tokens->next;
	}
	if (check_redirect_end(token))
		return (1);

	return (0);
}

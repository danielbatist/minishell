/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:20:21 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/06 10:38:54 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	validate_file(t_token *token, char *lexeme)
{
	struct stat	stat_buf;

	if (token->type == REDIRECT_OUT || token->type == APPEND)
	{
		if (access(lexeme, F_OK) == 0)
		{
			if (stat(lexeme, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
				return (print_error_direc_and_file(lexeme, IS_DIR));
			if (access(lexeme, W_OK) != 0)
				return (print_error_direc_and_file(lexeme, PERM_DENIED));
		}
		return (0);
	}
	if (token->type == REDIRECT_IN)
	{
		if (access(lexeme, F_OK) != 0)
			return (print_error_direc_and_file(lexeme, FILE_NOT_FOUND));
		if (stat(lexeme, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
			return (print_error_direc_and_file(lexeme, IS_DIR));
		if (access(lexeme, R_OK) != 0)
			return (print_error_direc_and_file(lexeme, PERM_DENIED));
	}
	return (0);
}

int	check_redirect_in(t_token *token, t_token *next)
{
	if (!next)
		return (print_error(token));
	if ((token->type == REDIRECT_IN && next->type == REDIRECT_IN) \
		|| (token->type == REDIRECT_IN && next->type == PIPE))
	{
		set_exit_status(2);
		return (print_error(next));
	}
	if (token->type == REDIRECT_IN)
	{
		set_exit_status(1);
		return (validate_file(token, next->lexeme));
	}
	return (0);
}

int	check_redirect_out(t_token *token, t_token *next)
{
	if (!next)
		return (print_error(token));
	if (token->type == REDIRECT_OUT || token->type == APPEND)
	{
		set_exit_status(1);
		return (validate_file(token, next->lexeme));
	}
	return (0);
}

int	check_redirects(t_token *token, t_token *next)
{
	if (!next)
		return (print_error(token));
	if (is_redirect(token->type) && is_redirect(next->type))
	{
		set_exit_status(2);
		return (print_error(next));
	}
	return (0);
}

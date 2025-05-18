/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:20:21 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/18 16:42:29 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	validate_output_file(char *lexeme)
{
	struct stat	stat_buf;

	if (access(lexeme, F_OK) == 0)
	{
		if (stat(lexeme, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
			return (print_error_direc_perm(lexeme, IS_DIR));
		if (access(lexeme, W_OK) != 0)
			return (print_error_direc_perm(lexeme, PERM_DENIED));
	}
	return (0);
}

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
	if (token->type == REDIRECT_OUT)
		return (validate_output_file(next->lexeme));
	return (0);
}

int	check_redirects(t_token *token, t_token *next)
{
	if (is_redirect(token->type) && is_redirect(next->type))
		return (print_error(next));
	return (0);
}

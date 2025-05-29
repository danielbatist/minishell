/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:56:02 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/29 15:59:57 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_error_direc_and_file(char *lexeme, t_is_command flag)
{
	if (flag == FILE_NOT_FOUND)
	{
		ft_printf_fd(2, "bash: %s: No such file or director\n", lexeme);
		return (1);
	}
	if (flag == IS_DIR)
	{
		ft_printf_fd(2, "bash: %s: Is a directory\n", lexeme);
		return (1);
	}
	else if (flag == PERM_DENIED)
	{
		ft_printf_fd(2, "bash: %s: Permission denied\n", lexeme);
		return (1);
	}
	return (0);
}

int	print_error(t_token *token)
{
	if (token->lexeme[0] == '\0')
	{
		ft_printf_fd(2, "-bash: syntax error");
		ft_printf_fd(2, " near unexpected token `newline'\n");
		return (1);
	}
	else if (token->type == UNCLOSED)
	{
		ft_printf_fd(2, "bash: %c syntax error", token->lexeme[0]);
		ft_printf_fd(2, "unexpected end of file (unclosed quote)\n");
		return (1);
	}
	else
	{
		ft_printf_fd(2, "-bash: syntax error");
		ft_printf_fd(2, "near unexpected token `%c'\n", token->lexeme[0]);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:56:02 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 20:25:35 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_dot_error(char *lexeme)
{
	ft_printf_fd(2, "bash: %c: filename argument required\n", lexeme[0]);
	ft_printf_fd(2, "%c: usage: %c ", lexeme[0], lexeme[0]);
	ft_printf_fd(2, "filename [arguments]\n");
	*get_exit_status() = 2;
}

int	print_error_direc_and_file(char *lexeme, t_is_command flag)
{
	if (flag == FILE_NOT_FOUND)
	{
		ft_printf_fd(2, "bash: %s: No such file or director\n", lexeme);
		return (1);
	}
	else if (flag == IS_DIR)
	{
		ft_printf_fd(2, "bash: %s: Is a directory\n", lexeme);
		return (1);
	}
	else if (flag == NOT_IS_DIR)
	{
		ft_printf_fd(2, "bash: %s: Not a directory\n", lexeme);
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
		return (2);
	}
	else if (token->type == UNCLOSED)
	{
		ft_printf_fd(2, "bash: %c syntax error ", token->lexeme[0]);
		ft_printf_fd(2, "unexpected end of file (unclosed quote)\n");
		return (2);
	}
	else
	{
		ft_printf_fd(2, "-bash: syntax error");
		ft_printf_fd(2, "near unexpected token `%c'\n", token->lexeme[0]);
		return (2);
	}
	return (0);
}

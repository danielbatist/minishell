/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:12:16 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 20:02:39 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_error(t_token *token)
{
	if (token->lexeme[0] == '\0')
	{
		ft_printf_fd(2, "-bash: syntax error");
		ft_printf_fd(2, " near unexpected token `newline'\n");
		return (1);
	}
	else if (token->type == TARGET)
	{
		ft_printf_fd(2, "bash: %s: No such file or director\n", token->lexeme);
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

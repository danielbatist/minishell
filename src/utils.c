/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:12:16 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/17 14:13:15 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_error(char c)
{
	if (c == '\0' || c == ' ')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else
	{
		printf("bash: syntax error near unexpected token `%c'\n", c);
		return (1);
	}
	return (0);
}

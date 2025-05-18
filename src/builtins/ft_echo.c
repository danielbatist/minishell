/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:20 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/02 18:05:55 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_list *tokens)
{
	t_token	*token;
	int		n_flag;
	int		first_arg;
	int		i;

	tokens = tokens->next;
	n_flag = 0;
	first_arg = 1;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->type == FLAG	&& token->lexeme[0] == '-' && ft_strncmp(token->lexeme, "-n", 2) == 0)
		{
			i = 2;
			while (token->lexeme[i] == 'n')
				i++;
			if (token->lexeme[i] == '\0')
			{
				n_flag = 1;
				tokens = tokens->next;
				continue ;
			}
		}
		break ;
	}
	while (tokens)
	{
		if (!first_arg)
			write(1, " ", 1);
		first_arg = 0;
		token = (t_token *)tokens->content;
		ft_printf_fd(1, token->lexeme);
		tokens = tokens->next;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}

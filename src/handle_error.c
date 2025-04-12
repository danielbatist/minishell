/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:02:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/11 21:00:12 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Error de | no inicio da string /
// Error de | no final da string /
// Error de  > no final da string /
// Error de > > espaço entre redirect
// Error de  >> > ou >>> e < << ou <<< mais de redirect em append ou heredoc

int	handle_error(t_list *tokens)
{
	t_token	*token;
	t_token *next;
	t_token *last_token = NULL;

	if (tokens && ((t_token *)tokens->content)->type == PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (tokens)
	{
		token = tokens->content;
		if (tokens->next)
			next = tokens->next->content;
		else
			next = NULL;
		if ((token->type == PIPE) && (next && next->type == PIPE))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
			return (1);

		}
		if ((token->type == REDIRECT_IN || token->type == REDIRECT_OUT \
			|| token->type == APPEND || token->type == HEREDOC) \
			&& (next->type != PARAMETER && next->type != TARGET \
			&& next->type != SINGLE_QUOTED && next->type != DOUBLE_QUOTED))
		{
			ft_putstr_fd("bash: syntax error near \
			unexpected token `newline'\n", 2);
			return (1);
		}
		last_token = token;
		tokens = tokens->next;
	}
	if (last_token && last_token->type == PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

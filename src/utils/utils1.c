/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:36:28 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 20:26:12 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_flag(t_scanner *scanner, char *s)
{
	if (*s != '-')
		return (0);
	if (scanner->src[scanner->current] == '-')
		return (1);
	if (scanner->src[scanner->current] != '\0'
		&& ft_isalnum(scanner->src[scanner->current]))
		return (1);
	return (0);
}

int	is_metachar(t_token_type type)
{
	return (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC || type == UNCLOSED);
}

int	is_redirect(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT \
	|| type == APPEND || type == HEREDOC);
}

void	redirects_token(t_list **token_list)
{
	*token_list = (*token_list)->next;
	if (*token_list)
		*token_list = (*token_list)->next;
}

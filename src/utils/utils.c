/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:24:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/24 18:39:43 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_token_type(int type)
{
	if (type == COMMAND)
		return ("COMMAND");
	if (type == FLAG)
		return ("FLAG");	
	if (type == PIPE)
		return ("PIPE");	
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");	
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");	
	if (type == APPEND)
		return ("APPEND");	
	if (type == HEREDOC)
		return ("HEREDOC");	
	if (type == TARGET)
		return ("TARGET");	
	if (type == PARAMETER)
		return ("PARAMETER");	
	if (type == SINGLE_QUOTED)
		return ("SINGLE_QUOTED");	
	if (type == DOUBLE_QUOTED)
		return ("DOUBLE_QUOTED");	
	if (type == UNCLOSED)
		return ("UNCLOSED");	
	if (type == EOF_TOKEN)
		return ("EOF_TOKEN");
	return ("UNKNOWN");	
}

int	is_flag(t_scanner *scanner, char *s)
{
	if (*s != '-')
		return (0);
	if (scanner->src[scanner->current] == '-')
		return (1);
	if (scanner->src[scanner->current] != '\0' && ft_isalnum(scanner->src[scanner->current]))
		return (1);
	return (0);
}

int	is_metachar(t_token_type type)
{
	return (type == PIPE || type ==  REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC || type == UNCLOSED);
}

int	is_redirect(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT \
	|| type == APPEND || type == HEREDOC);
}

int	tokens_len(t_scanner *scanner)
{
	t_list	*tmp;
	int		i;

	tmp = scanner->tokens;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	redirects_token(t_list **token_list)
{
	*token_list = (*token_list)->next;
	if (*token_list)
		*token_list = (*token_list)->next;
}

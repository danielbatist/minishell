/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:36:10 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/03 16:12:35 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	print_token_list(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		printf("[TOKEN] lexeme: '");
		if (token->lexeme)
			printf("%s", token->lexeme);
		else
			printf("(null)");
		printf("' | type: %s | plus: %d\n", get_token_type(token->type), token->plus);
		tokens = tokens->next;
	}
}

void	print_commands(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i].simple_command)
	{
		printf("Simple Command %d\n", i);
		j = 0;
		while (cmd[i].simple_command[j])
		{
			printf(" %s\n", cmd[i].simple_command[j]);
			j++;
		}
		i++;
	}
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

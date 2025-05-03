/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:36:10 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/02 21:17:06 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_token_list(t_list *tokens)
{
	t_token *token;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		printf("[TOKEN] lexeme: '%s' | type: %d | plus: %d\n", token->lexeme, token->type, token->plus);
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

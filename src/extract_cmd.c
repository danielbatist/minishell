/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:29:06 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/10 14:04:38 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_cmd_tokens(t_list *current)
{
	int		count;

	count = 0;
	while (current && ((t_token *)(current->content))->type != PIPE)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static int	should_join_token(t_token *current, t_token *next)
{
	if (!next)
		return (0);
	if (!(current->type == DOUBLE_QUOTED || current->type == SINGLE_QUOTED
			|| current->type == PARAMETER))
		return (0);
	if (is_metachar(next->type))
		return (0);
	if (next->has_space == TRUE)
		return (0);
	if (current->plus == TRUE)
		return (1);
	return (0);
}

static char	*join_tokens_loop(t_list **token_list, t_token *current)
{
	char	*joined;
	char	*tmp;
	t_token	*next;

	joined = ft_strdup(current->lexeme);
	while ((*token_list)->next)
	{
		next = (t_token *)(*token_list)->next->content;
		if (!should_join_token(current, next))
			break ;
		*token_list = (*token_list)->next;
		current = (t_token *)(*token_list)->content;
		tmp = ft_strjoin(joined, current->lexeme);
		free(joined);
		joined = tmp;
	}
	return (joined);
}

static void	handle_token_join(t_list **tokens, char **cmd, int *i)
{
	t_token	*token;
	char	*joined;

	token = (t_token *)(*tokens)->content;
	joined = join_tokens_loop(tokens, token);
	cmd[*i] = joined;
	printf("Token %d: %s, plus: %d, has space: %d\n",
		*i + 1, token->lexeme, token->plus, token->has_space);
	*i += 1;
}

char	**extract_simple_cmd(t_list **token_list)
{
	char	**cmd;
	int		count;
	int		i;

	count = count_cmd_tokens(*token_list);
	i = 0;
	cmd = ft_calloc(count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	printf("Parser status token:\n");
	while (*token_list && ((t_token *)(*token_list)->content)->type != PIPE)
	{
		handle_token_join(token_list, cmd, &i);
		*token_list = (*token_list)->next;
	}
	if (*token_list && ((t_token *)(*token_list)->content)->type == PIPE)
		*token_list = (*token_list)->next;
	return (cmd);
}

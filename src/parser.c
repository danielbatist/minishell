/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:14:47 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/09 20:25:25 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	count_pipes(t_scanner *scanner)
{
	t_list	*current;
	t_token	*token;
	int		count;

	count = 0;
	current = scanner->tokens;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}


char **extract_simple_cmd(t_list **token_list)
{
	t_token	*token;
	t_token	*next_token;
	t_list	*start;
	t_list	*current;
	int		count;
	char	**cmd;
	char	*tmp;
	char	*joined;
	int		i;

	start = *token_list;
	count = 0;
	current = start;
	while (current && ((t_token *)(current->content))->type != PIPE)
	{
		count++;
		current = current->next;
	}
	cmd = ft_calloc(count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	*token_list = start;
	i = 0;
	printf("Parser status token:\n");
	while (*token_list && ((t_token *)(*token_list)->content)->type != PIPE)
	{
		token = (t_token *)(*token_list)->content;
		joined = ft_strdup(token->lexeme);
		if (!joined)
			return (NULL);
		while ((*token_list)->next)
		{
			next_token = (t_token *)(*token_list)->next->content;
			if (token->plus == TRUE && next_token->has_space == FALSE
				&& (token->type == DOUBLE_QUOTED || token->type == PARAMETER
				|| token->type == SINGLE_QUOTED) && !(is_metachar(next_token->type)))
			{
				*token_list = (*token_list)->next;
				token = (t_token *)(*token_list)->content;
				tmp = ft_strjoin(joined, next_token->lexeme);
				free(joined);
				joined = tmp;
			}
			else
				break ;
		}
		cmd[i++] = joined;
		*token_list = (*token_list)->next;
		printf("Token %d: %s, Plus: %d, Has space: %d\n", i, token->lexeme, token->plus, token->has_space);
	}
	printf("\n");
	if (*token_list && ((t_token *)(*token_list)->content)->type == PIPE)
		*token_list = (*token_list)->next;
	return (cmd);
}

t_command	*parser(char *input, t_list *env_list)
{
	t_scanner	*scanner;
	t_command	*complex_command;
	int			i;
	int			cmds_count;
	t_list		*current;

	i = 0;
	scanner = init_scanner(input);
	if (!scanner)
		return (NULL);
	scan_tokens(scanner);
	env_expansion(env_list, scanner);
	print_token_list(scanner->tokens);
	if (!scanner->tokens || handle_error(scanner->tokens))
	{
		free_scanner(scanner);
		return (NULL);
	}
	cmds_count = count_pipes(scanner) + 1;
	complex_command = ft_calloc(cmds_count + 1, sizeof(t_command));
	if (!complex_command)
	{
		free_scanner(scanner);
		return (NULL);
	}
	current = scanner->tokens;
	while (current && i < cmds_count)
	{
		complex_command[i].simple_command = extract_simple_cmd(&current);
		i++;
	}
	free_scanner(scanner);
	return (complex_command);
}

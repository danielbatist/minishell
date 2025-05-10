/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:14:47 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/10 17:56:36 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_scanner	*init_and_scan(char *input, t_list *env_list)
{
	t_scanner	*scanner;

	scanner = init_scanner(input);
	if (!scanner)
		return (NULL);
	scan_tokens(scanner);
	env_expansion(env_list, scanner);
	print_token_list(scanner->tokens);
	return (scanner);
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
//free_and_return

t_command	*parser(char *input, t_list *env_list)
{
	t_scanner	*scanner;
	t_command	*commands;
	t_list		*current;
	int			cmds_count;
	int			i;

	scanner = init_and_scan(input, env_list);
	if (!scanner || !scanner->tokens || handle_error(scanner->tokens))
		return (free_and_return(scanner));
	cmds_count = count_pipes(scanner) + 1;
	commands = ft_calloc(cmds_count + 1, sizeof(t_command));
	if (!commands)
		return (free_and_return(scanner));
	current = scanner->tokens;
	i = 0;
	while (current && i < cmds_count)
		commands[i++].simple_command = extract_simple_cmd(&current);
	free_scanner(scanner);
	return (commands);
}

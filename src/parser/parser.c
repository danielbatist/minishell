/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:14:47 by eteofilo          #+#    #+#             */
/*   Updated: 2025/06/11 18:03:45 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_scanner	*init_and_scan(char *input, t_list *env_list)
{
	t_scanner	*scanner;

	scanner = init_scanner(input);
	if (!scanner)
		return (NULL);
	scan_tokens(scanner);
	env_expansion(env_list, scanner);
	//print_token_list(scanner->tokens);
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

t_command	*extract_command(t_list **token_list, t_list *env_list,
		t_scanner *scanner, int cmds_count)
{
	t_command	*cmd;
	t_list		*start;
	int			i;

	cmd = ft_calloc(cmds_count + 1, sizeof(t_command));
	if (!cmd)
		return (free_and_return(scanner));
	i = 0;
	while (i < cmds_count)
	{
		start = *token_list;
		cmd[i].is_heredoc = FALSE;
		cmd[i].error_flag = FALSE;
		cmd[i].fd_in = STDIN_FILENO;
		cmd[i].fd_out = STDOUT_FILENO;
		cmd[i].env_list = env_list;
		cmd[i].simple_command = extract_simple_cmd(token_list);
		if (handle_redirects(start, &cmd[i], scanner))
			cmd[i].error_flag = TRUE;
		i++;
	}
	return (cmd);
}

t_command	*parser(char *input, t_list *env_list)
{
	t_scanner	*scanner;
	t_command	*commands;
	t_list		*current;
	int			cmds_count;


	scanner = init_and_scan(input, env_list);
	if (!scanner || !scanner->tokens || handle_error(scanner->tokens))
		return (free_and_return(scanner));
	cmds_count = count_pipes(scanner) + 1;
	current = scanner->tokens;
	commands = extract_command(&current, env_list, scanner, cmds_count);
	//print_commands(commands);
	free_scanner(scanner);
	return (commands);
}

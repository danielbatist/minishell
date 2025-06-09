/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:14:47 by eteofilo          #+#    #+#             */
/*   Updated: 2025/06/09 00:14:35 by dbatista         ###   ########.fr       */
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

t_command	extract_command(t_list **token_list, t_list *env_list)
{
	t_command	cmd;
	t_list		*start;

	ft_bzero(&cmd, sizeof(t_command));
	start = *token_list;
	cmd.is_heredoc = FALSE;
	cmd.error_flag = FALSE;
	cmd.fd_in = STDIN_FILENO;
	cmd.fd_out = STDOUT_FILENO;
	cmd.simple_command = extract_simple_cmd(token_list);
	if (handle_redirects(start, &cmd, env_list))
		cmd.error_flag = TRUE;
	return (cmd);
}

t_command	*parser(char *input, t_list *env_list)
{
	t_scanner	*scanner;
	t_command	*commands;
	t_list		*current;
	int			cmds_count;
	int			i;

	scanner = init_and_scan(input, env_list);
	if (!scanner || !scanner->tokens || handle_error(scanner->tokens))
	{
		ft_printf_fd(2, "status: %d\n", *get_exit_status());
		return (free_and_return(scanner));
	}
	cmds_count = count_pipes(scanner) + 1;
	commands = ft_calloc(cmds_count + 1, sizeof(t_command));
	if (!commands)
		return (free_and_return(scanner));
	current = scanner->tokens;
	i = 0;
	while (current && i < cmds_count)
		commands[i++] = extract_command(&current, env_list);
	free_scanner(scanner);
	return (commands);
}

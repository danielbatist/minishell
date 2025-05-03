/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:14:47 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/02 21:28:35 by dbatista         ###   ########.fr       */
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

char	*concat_token(t_list *token_list)
{
	char	*tmp1;
	char	*tmp2;

	if (!token_list || !token_list->next)
		return (NULL);
	if (!token_list->content || !token_list->next->content)
		return (NULL);
	tmp1 = ((t_token *)(token_list->content))->lexeme;
	tmp2 = ((t_token *)(token_list->next->content))->lexeme;
	if (!tmp1 || !tmp2)
		return (NULL);
	return (ft_strjoin(tmp1, tmp2));
}

char **extract_simple_cmd(t_list **token_list)
{
	t_token	*token;
	t_list *start;
	int		count;
	char	**cmd;
	int		i;

	start = *token_list;
	count = 0;
	while (*token_list && ((t_token *)(*token_list)->content)->type != PIPE)
	{
		count++;
		*token_list = (*token_list)->next;
	}
	cmd = ft_calloc(count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	*token_list = start;
	i = 0;
	while (i < count && *token_list)
	{
		if (!(*token_list) || !(*token_list)->content)
			break ;
		token =(t_token *)(*token_list)->content;
		if (token->plus == TRUE && (*token_list)->next && (*token_list)->next->content)
		{
			cmd[i] = concat_token(*token_list);
			if (!cmd[i])
			{
				printf("Error ao concatenar");
				return (NULL);
			}
			printf("token: %s, plus: %d\n", token->lexeme, token->plus);
			*token_list = (*token_list)->next->next;

		}
		else
		{
			cmd[i] = ft_strdup(token->lexeme);
			*token_list = (*token_list)->next;
		}
		i++;
	}
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

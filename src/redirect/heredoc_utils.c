/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:40:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/24 18:41:01 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*here_exp(char *line, t_list *env_list)
{
	t_token		*token;
	t_list		*list;
	t_scanner	scanner;
	char		*new_line;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexeme = ft_strdup(line);
	token->type = TARGET;
	list = ft_lstnew(token);
	scanner.tokens = list;
	env_expansion(env_list, &scanner);
	new_line = ft_strdup(token->lexeme);
	ft_lstdelone(list, free_token);
	return (new_line);
}

void	clean_heredoc(t_command *cmd)
{
	if (cmd->heredoc_file && cmd->is_heredoc)
	{
		unlink(cmd->heredoc_file);
		free(cmd->heredoc_file);
		cmd->heredoc_file = NULL;
	}
}

char	*create_tmp_file(void)
{
	static int		index = 0;
	char			*filename;
	char			*idx_str;

	idx_str = ft_itoa(index++);
	filename = ft_strjoin("/tmp/.heredoc_tmp", idx_str);
	free(idx_str);
	return (filename);
}

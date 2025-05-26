/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:02:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/26 18:04:12 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->lexeme)
		free(token->lexeme);
	free(content);
}

void	free_complex_command(t_command *cmds)
{
	char	**simple;
	int		i;
	int		j;

	i = 0;
	if (!cmds)
		return ;
	while (cmds[i].simple_command)
	{
		simple = cmds[i].simple_command;
		j = 0;
		while (simple[j])
			free(simple[j++]);
		free(simple);
		free(cmds[i].infile);
		free(cmds[i].outfile);
		free(cmds[i].append_file);
		free(cmds[i].heredoc_delim);
		i++;
	}
	free (cmds);
}

void	free_env_list(t_list *env_list)
{
	t_list	*tmp;
	t_env	*env;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		env = (t_env *)tmp->content;
		if (env)
		{
			free(env->name);
			free(env->value);
			free(env);
		}
		free(tmp);
	}
}

void	free_scanner(t_scanner *scanner)
{
	if (!scanner)
		return ;
	if (scanner->tokens)
		ft_lstclear(&scanner->tokens, free_token);
	free(scanner);
}

t_command	*free_and_return(t_scanner *scanner)
{
	if (scanner)
		free_scanner(scanner);
	return (NULL);
}

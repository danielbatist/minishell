/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:32:48 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/10 10:33:04 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env(t_env **env)
{
	if (!env || !*env)
		return ;
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = NULL;
}

void	free_list_and_env(t_list *tmp_list, t_env *env)
{
	free(((t_env *)(tmp_list->content))->value);
	((t_env *)(tmp_list->content))->value = env->value;
	free(env->name);
	free(env);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:41:04 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/07 18:48:26 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_var(char *var)
{
	int	i;

	i = 1;
	if (!var || !ft_isalpha(var[0]))
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_var(t_list **env_list, char *var)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		env = (t_env *)current->content;
		if (!ft_strcmp(env->name, var))
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(env->name);
			free(env->value);
			free(env);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->simple_command[i])
	{
		if (is_valid_var(cmd->simple_command[i]))
			remove_env_var(&cmd->env_list, cmd->simple_command[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:41:09 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/06 22:33:07 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_errors(char *cmd)
{
	int	i;

	if (!cmd || (!ft_isalpha(cmd[0]) && cmd[0] != '_'))
	{
		ft_printf_fd(2, "export: '%s': not a valid identifier\n", cmd);
		return (1);
	}
	i = 1;
	while ((cmd[i]) && (cmd[i] != '='))
	{
		if ((!ft_isalnum(cmd[i])) && (cmd[i] != '='))
		{
		ft_printf_fd(2, "export: '%s': not a valid identifier\n", cmd);
		return (1);
		}
		i++;
	}
	return (0);
}

t_env	*is_env(char *cmd, t_list **tmp_list, t_list *env_list)
{
	int		i;
	t_env	*env;

	i = 0;
	env = (t_env *)malloc(sizeof(t_env));
	env->value = NULL;
	while (cmd[i] && cmd[i] != '=')
		i++;
	env->name = ft_substr(cmd, 0, i);
	if (cmd[i])
		env->value = ft_substr(cmd, i + 1, ft_strlen(cmd));
	*tmp_list = env_list;
	while (*tmp_list)
	{
		if (ft_strncmp(env->name, ((t_env *)((*tmp_list)->content))->name,
			ft_strlen(env->name)) == 0)
			break ;
		*tmp_list = (*tmp_list)->next;
	}
	return (env);
}

void	free_env(t_env **env)
{
	free((*env)->name);
	free(*env);
}

int	ft_export(char **cmd, t_list *env_list)
{
	int		i;
	t_list	*tmp_list;
	t_env	*env;

	i = 1;
	env = NULL;
	while (cmd[i])
	{
		if (get_errors(cmd[i]))
		{
			set_exit_status(1);
			i++;
			continue ;
		}
		env = is_env(cmd[i], &tmp_list, env_list);
		if (tmp_list && env->value)
		{
			free(((t_env *)(tmp_list->content))->value);
			((t_env *)(tmp_list->content))->value = env->value;
			free_env(&env);
		}
		else if (env->value)
			ft_lstadd_back(&env_list, ft_lstnew(env));
		else
			free_env(&env);
		i++;
	}
	return (1);
}

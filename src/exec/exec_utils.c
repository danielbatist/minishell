/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:00 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/29 15:49:31 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(t_list *env_list, const char *name)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
			return (env->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_list *env_list)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_var = get_env_value(env_list, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_triple(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	free_exec(paths);
	return (NULL);
}

char	**get_envp(t_list *env_list)
{
	int		count;
	char	**envp;
	t_env	*env;
	int		i;

	count = ft_lstsize(env_list);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		env = (t_env *)env_list->content;
		envp[i++] = ft_strjoin_triple(env->name, "=", env->value);
		env_list = env_list->next;
	}
	envp[i] = NULL;
	return (envp);
}

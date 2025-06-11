/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:20:43 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 17:59:49 by dbatista         ###   ########.fr       */
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

char	*search_in_path(char *cmd, char *path_var)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_triple(paths[i++], "/", cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	free_exec(paths);
	return (NULL);
}

char	*get_path(char *cmd, t_list *env_list)
{
	char	*path_var;

	if (ft_strncmp(cmd, "..", 2) == 0)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}	
	path_var = get_env_value(env_list, "PATH");
	if (!path_var)
		return (NULL);
	return (search_in_path(cmd, path_var));
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

void	execute_child(t_command *cmd, int i, int is_pipe, t_pipefd *pipefd)
{
	char	*path;
	char	**envp;

	set_signal_child();
	dup2_pipes(pipefd, is_pipe, &i);
	close_pipes(pipefd, is_pipe);
	if (open_redirect(&cmd[i]) < 0)
		exit (1);
	dup2_redirect(&cmd[i]);
	if (cmd[i].simple_command && cmd[i].simple_command[0])
	{
		envp = get_envp(cmd[i].env_list);
		path = get_path(cmd[i].simple_command[0], cmd[i].env_list);
		if (!path)
			free_child_not_found(path, envp, cmd, &i);
		execve(path, cmd[i].simple_command, envp);
		free(path);
		free_exec(envp);
		exit(1);
	}
	free_env_list(cmd->env_list);
	free(cmd->data->pids);
	free(cmd->data);
	free_complex_command(cmd);
	exit(0);
}

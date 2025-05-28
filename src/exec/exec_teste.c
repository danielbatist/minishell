/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_teste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:04:24 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/28 19:06:51 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*get_env_value(t_list *env_list, const char *name)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		if (ft_strncmp(env->name, name, ft_strlen(name)))
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
	free_paths(paths);
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

void	execute_command(t_command *cmd, t_list *env_list)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	pid = fork();
	if (pid == 0)
	{
		if (open_redirect(cmd) < 0)
			exit (1);
		dup_redirect(cmd);
		if (cmd->simple_command && cmd->simple_command[0])
		{
			envp = get_envp(env_list);
			path = get_path(cmd->simple_command[0], env_list);
			if (!path)
			{
				ft_printf_fd(2, "minishell: command not found: %s\n", cmd->simple_command[0]);
				free(envp);
				exit(127);
			}
			execve(path, cmd->simple_command, envp);
			ft_printf_fd(2, "minishell: Erro ao executar %s\n", path);
			free(path);
			free_envp(envp);
			exit(1);
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		clean_heredoc(cmd);
	}
}

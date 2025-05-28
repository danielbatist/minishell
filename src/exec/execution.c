/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:17:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/28 19:08:58 by dbatista         ###   ########.fr       */
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

void	execute_parent(t_exec *data, t_command *cmd, int *i)
{
	int		j;

	j = 0;
	clean_heredoc(cmd);
	if (*i > 0)
		close(data->pipefd[*i - 1].fd[0]);
	if (*i < data->is_pipe)
		close(data->pipefd[*i].fd[1]);
	while (j <= data->is_pipe)
	{
		waitpid(data->pids[j], NULL, 0);
		j++;
	}
}

void	execute_child(t_command *cmd, int i, int is_pipe, t_pipefd *pipefd)
{
	char	*path;
	char	**envp;
	int		j;

	if (i > 0 && is_pipe > 0)
		dup2(pipefd[i - 1].fd[0], STDIN_FILENO);
	if (i < is_pipe)
		dup2(pipefd[i].fd[1], STDOUT_FILENO);
	j = 0;
	while (j < is_pipe && is_pipe > 0)
	{
		close(pipefd[j].fd[0]);
		close(pipefd[j].fd[1]);
		j++;
	}
	if (open_redirect(&cmd[i]) < 0)
		exit (1);
	dup_redirect(&cmd[i]);
	if (cmd[i].simple_command && cmd[i].simple_command[0])
	{
		envp = get_envp(cmd[i].env_list);
		path = get_path(cmd[i].simple_command[0], cmd[i].env_list);
		if (!path)
		{
			ft_printf_fd(2, "minishell: command not found: %s\n", cmd[i].simple_command[0]);
			free_envp(envp);
			exit(127);
		}
		execve(path, cmd->simple_command, envp);
		free(path);
		free_envp(envp);
		exit(1);
	}
	exit(0);
}

void	execute_commands(t_command *cmd, t_exec *data, t_list *env_list)
{
	int	i;

	i = 0;
	while (cmd[i].simple_command)
		cmd[i++].env_list = env_list;
	i = 0;
	while ((cmd[i].simple_command))
	{
		if (cmd[i].error_flag)
		{
			clean_heredoc(&cmd[i]);
			i++;
			continue ;
		}
		data->is_builtin = FALSE;
		if (data->is_pipe > 0 || !data->is_builtin)
		{
			data->pids[i] = fork();
			if (data->pids[i] == 0)
				execute_child(cmd, i, data->is_pipe, data->pipefd);
			else
				execute_parent(data, cmd, &i);
			i++;
		}
	}
}


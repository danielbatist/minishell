/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:41:12 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/06 21:36:17 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	valide_cd(char *path, char *cmd)
{
	struct stat	stat_buf;

	if (stat(path, &stat_buf) != 0)
		print_error_direc_and_file(cmd, FILE_NOT_FOUND);
	else if (!S_ISDIR(stat_buf.st_mode))
		print_error_direc_and_file(cmd, NOT_IS_DIR);
	else if (access(path, X_OK) != 0)
		print_error_direc_and_file(cmd, PERM_DENIED);
}

int	ft_cd(char **cmd, t_list *env_list)
{
	char		*home;
	char		*path;
	
	path = NULL;
	home = search_env("HOME", env_list);
	if (!cmd[1] || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		path = ft_strdup(home);
	else if (cmd[1][0] == '~')
		path = ft_strjoin(home, cmd[1] + 1);
	else
		path = ft_strdup(cmd[1]);
	valide_cd(path, cmd[1]);
	chdir(path);
	free(path);
	free(home);
	return (1);
}

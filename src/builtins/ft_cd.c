/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:41:12 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/04 17:52:49 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(char **cmd, t_list *env_list)
{
	char	*home;
	char	*path;

	path = NULL;
	home = search_env("HOME", env_list);
	if (!cmd[1] || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		chdir(home);
	else if (cmd[1][0] == '~')
	{
		path = ft_strjoin(home, cmd[1] + 1);
		chdir(path);
		free(path);
	}
	else
		chdir(cmd[1]);
	free(home);
	return (1);
}

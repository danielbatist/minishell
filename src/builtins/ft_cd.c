/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:41:12 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/02 16:41:14 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_cd(char **cmd)
{
    char *home;

    home = search_env("HOME", env_list);
    if (!cmd[1])
        chdir(home);
    else
        chdir(cmd[1]);
    free(home);
    return (1);
}
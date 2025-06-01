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

    home = getenv("HOME");
    if (!cmd && !cmd[1] && !cmd[1][0])
        chdir(home);
    chdir(cmd[1]);
    return (1);
}
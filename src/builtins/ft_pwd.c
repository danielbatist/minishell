/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:41:26 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/02 16:41:27 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_pwd(char **cmd)
{
    char *pwd;

    if (cmd && cmd[1] && cmd[1][0])
    {
        ft_printf_fd(1, "pwd: too many arguments");
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (pwd != NULL)
	{
        ft_printf_fd(1, pwd);
        return (1);
    }
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:20 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/02 18:05:55 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(char **cmd)
{
	int		i;
	int		j;
	int		suppress_newline;
	int is_printed;

	suppress_newline = 0;
	is_printed = 0;
	i = 1;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			j = 2;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] == '\0')
				suppress_newline = 1;
		}
		else
		{
			ft_printf_fd(1, cmd[i]);
			ft_printf_fd(1, " ");
		}
		is_printed = 1;
		i++;
	}
	if (!suppress_newline)
	{
		ft_printf_fd(1, "\n");
		printf("Tem newline\n");
	}
	return (is_printed);
}

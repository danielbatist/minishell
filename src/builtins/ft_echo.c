/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:20 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/07 18:08:48 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../../inc/minishell.h"

void	print_echo(char **cmd, int *i, int suppress_newline)
{
	while (cmd[*i])
	{
		ft_printf_fd(1, "%s", cmd[*i]);
		if (cmd[*i + 1])
			ft_printf_fd(1, " ");
		(*i)++;
	}
	if (!suppress_newline)
		ft_printf_fd(1, "\n");
}

int	ft_echo(char **cmd)
{
	int		i;
	int		j;
	int		suppress_newline;

	suppress_newline = 0;
	i = 1;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			j = 2;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] == '\0')
			{
				suppress_newline = 1;
				i++;
				continue ;
			}
		}
		break ;
	}
	print_echo(cmd, &i, suppress_newline);
	return (1);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:39:40 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/07 18:23:13 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strisdigit(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_status(char **args)
{
	if (!args || !args[0])
	{
		printf("exit\n");
		exit(0);
	}
	if (args[1] && args[2])
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (args[1])
	{
		if (!ft_strisdigit(args[1]))
		{
			printf("exit\n");
			ft_printf_fd(2, "minishell: exit:");
			ft_printf_fd(2, "%s: numeric argument required\n", args[1]);
			exit(2);
		}
		set_exit_status(ft_atoi(args[1]) % 256);
	}
	return (0);
}

int	ft_exit(t_command *cmd)
{
	char	**args;
	int		status;

	status = 0;
	args = cmd->simple_command;
	validate_status(args);
	status = *get_exit_status();
	printf("exit\n");
	exit(status);
}

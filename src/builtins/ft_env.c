/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:39:50 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/07 18:25:07 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_list *env_list)
{
	t_list	*tmp_list;

	tmp_list = env_list;
	while (tmp_list)
	{
		ft_printf_fd(1, "%s=%s\n", ((t_env *)(tmp_list->content))->name,
			((t_env *)(tmp_list->content))->value);
		tmp_list = tmp_list->next;
	}
	return (1);
}

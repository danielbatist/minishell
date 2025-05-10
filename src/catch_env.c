/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:20:43 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/10 09:57:58 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*catch_env(char **envp)
{
	t_list	*env_list;
	t_env	*env;
	int		i;

	env = NULL;
	env_list = NULL;
	while (*envp)
	{
		i = 0;
		while ((*envp)[i] && (*envp)[i] != '=')
			i++;
		env = malloc(sizeof(t_env));
		env->name = ft_substr(*envp, 0, i);
		env->value = ft_substr(*envp, i + 1, ft_strlen(*envp));
		ft_lstadd_back(&env_list, ft_lstnew(env));
		env = NULL;
		envp++;
	}
	return (env_list);
}

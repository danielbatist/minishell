/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:02:10 by eteofilo          #+#    #+#             */
/*   Updated: 2025/04/14 15:22:25 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*expansion(char **envp)
{
	char	**strings;
	t_list	*env_list;
	t_env	*env;

	env = malloc(sizeof(t_env));
	strings = ft_split(*envp++, '=');
	env->name = strings[0];
	env->value = strings[1];
	env_list = ft_lstnew(env);
	env = NULL;
	while(*envp)
	{
		env = malloc(sizeof(t_env));
		strings = ft_split(*envp++, '=');
		env->name = strings[0];
		env->value = strings[1];
		ft_lstadd_back(&env_list, ft_lstnew(env));
		env = NULL;
	}
	return (env_list);
}

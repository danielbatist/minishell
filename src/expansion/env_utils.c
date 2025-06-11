/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:42:22 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/24 17:54:04 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*search_env(char *str, t_list *env_list)
{
	t_list	*tmp_list;
	char	*tmp_str;
	char	*str_return;

	tmp_list = env_list;
	while (tmp_list)
	{
		tmp_str = ((t_env *)(tmp_list->content))->name;
		if (ft_strncmp(str, tmp_str, ft_strlen(str) + 1) == 0)
		{
			str_return = ft_strdup(((t_env *)(tmp_list->content))->value);
			return (str_return);
		}
		tmp_list = tmp_list->next;
	}
	return (NULL);
}

char	*join_replacement(char *str, int start, int end, char *env_value)
{
	char	*prefix;
	char	*sufix;
	char	*str_tmp;
	char	*str_return;

	prefix = ft_substr(str, 0, start);
	sufix = ft_substr(str, start + end + 1, ft_strlen(str));
	str_tmp = ft_strjoin(prefix, env_value);
	str_return = ft_strjoin(str_tmp, sufix);
	free(prefix);
	free(sufix);
	free(str_tmp);
	return (str_return);
}

char	*set_env(char *str, int start, int end, t_list *env_list)
{
	char	*env_key;
	char	*env_value;
	char	*str_return;

	env_key = ft_substr(str, start + 1, end);
	if (!env_key)
		return (NULL);
	env_value = search_env(env_key, env_list);
	free(env_key);
	if (!env_value)
		env_value = ft_strdup("");
	str_return = join_replacement(str, start, end, env_value);
	free(env_value);
	return (str_return);
}

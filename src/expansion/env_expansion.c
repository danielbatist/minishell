/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:02:10 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/23 00:03:56 by dbatista         ###   ########.fr       */
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

char *search_env(char *str, t_list *env_list)
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

char	*set_env(char *str, int start, int end, t_list *env_list)
{
	char	*env_key;
	char	*env_value;
	char	*prefix;
	char	*sufix;
	char	*str_tmp;
	char	*str_return;

	env_key = ft_substr(str, start + 1, end);
	if (!env_key)
		return (NULL);
	env_value = search_env(env_key, env_list);
	free(env_key);
	if (!env_value)
		env_value = ft_strdup("");
	prefix = ft_substr(str, 0, start);
	sufix = ft_substr(str, start + end + 1, ft_strlen(str));
	str_tmp = ft_strjoin(prefix, env_value);
	str_return = ft_strjoin(str_tmp, sufix);
	free(prefix);
	free(sufix);
	free(env_value);
	free(str_tmp);
	return (str_return);
}

void	scan_env(t_token *token, t_list *env_list)
{
	int		i;
	int		start;
	int		end;
	char	*str_env;

	i = 0;
	start = -1;
	end = 0;
	while (token->lexeme[i])
	{
		if (token->lexeme[i] == '$')
		{
			if (token->lexeme[i + 1] == '\0' || token->lexeme[i + 1] == ' ')
			{
				i++;
				continue ;
			}
			else if (token->lexeme[i + 1] == '?')
			{
				i += 2;
				continue ;
			}
			start = i;
			end = get_end(token->lexeme + i + 1);
			str_env = set_env(token->lexeme, start, end, env_list);
			if (str_env)
			{
				free(token->lexeme);
				token->lexeme = str_env;
				i = 0;
				continue ;
			}
		}
		i++;
	}
}

void	env_expansion(t_list *env_list, t_scanner *scanner)
{
	t_token	*token;
	t_list	*tmp_tokens;

	tmp_tokens = scanner->tokens;
	while (tmp_tokens)
	{
		token = (t_token *)tmp_tokens->content;
		if (token->type != SINGLE_QUOTED)
			scan_env(token, env_list);
		tmp_tokens = tmp_tokens->next;
	}
}

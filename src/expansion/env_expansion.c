/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:02:10 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/20 20:22:08 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '$')
		i++;
	return (i);
}

char *search_env(char *str, t_list *env_list)
{
	t_list	*tmp_list;
	char	*tmp_str;
	char	*str_return;
	int		is_env;

	tmp_list = env_list;
	is_env = 0;
	while (tmp_list)
	{
		tmp_str = ((t_env *)(tmp_list->content))->name;
		if (ft_strncmp(str, tmp_str, ft_strlen(str) + 1) == 0)
		{
			str_return = ft_strdup(((t_env *)(tmp_list->content))->value);
			free(str);
			return (str_return);
		}
		tmp_list = tmp_list->next;
	}
	return (NULL);
}

char	*set_env(char *str, int start, int end, t_list *env_list)
{
	char	*str_env;
	char	*str_tmp;
	char	*str_return;

	str_env = search_env(ft_substr(str, start+1, end), env_list);
	if(str_env == NULL)
		return(NULL);
	if (start == 0)
	{
		str_tmp = ft_substr(str, end+1, ft_strlen(str));
		str_return = ft_strjoin(str_env, str_tmp);
	}
	else
	{
		str_tmp = ft_substr(str, 0, start);
		str_return = ft_strjoin(str_tmp, str_env);
		free(str_tmp);
		free(str_env);
		str_tmp = ft_substr(str, start + end + 1, ft_strlen(str));
		str_env = str_return;
		str_return = ft_strjoin(str_env, str_tmp);
	}
	free(str_env);
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
	while (token->lexeme[i] && token->lexeme[i] != '$')
		i++;
	if (token->lexeme[i] == '$')
	{
		start = i;
		end = get_end(token->lexeme + i + 1);
		str_env = set_env(token->lexeme, start, end, env_list);
		if (str_env)
		{
			free(token->lexeme);
			token->lexeme = str_env;
		}
	}
}

void	env_expansion(t_list *env_list, t_scanner *scanner)
{
	t_list	*tmp_tokens;

	tmp_tokens = scanner->tokens;
	while(tmp_tokens)
	{
		if (((t_token *)(scanner->tokens->content))->type == COMMAND
			|| ((t_token *)(scanner->tokens->content))->type == FLAG
			|| ((t_token *)(scanner->tokens->content))->type == PARAMETER
			|| ((t_token *)(scanner->tokens->content))->type == TARGET
			|| ((t_token *)(scanner->tokens->content))->type == DOUBLE_QUOTED
		)
			scan_env(((t_token *)(tmp_tokens->content)), env_list);
		tmp_tokens = tmp_tokens->next;
	}
}

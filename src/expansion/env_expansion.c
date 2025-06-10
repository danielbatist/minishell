/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:02:10 by eteofilo          #+#    #+#             */
/*   Updated: 2025/06/09 12:26:22 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*replace_exit_status(char *lexeme, int i)
{
	char	*new_lexeme;
	char	*exit_str;
	int		len;
	int		status;

	status = *get_exit_status();
	exit_str = ft_itoa(status);
	if (!exit_str)
		return (NULL);
	len = ft_strlen(lexeme) - 1 + ft_strlen(exit_str);
	new_lexeme = malloc(len + 1);
	if (!new_lexeme)
	{
		free(exit_str);
		return (NULL);
	}
	ft_strlcpy(new_lexeme, lexeme, i + 1);
	ft_strlcat(new_lexeme, exit_str, len + 1);
	ft_strlcat(new_lexeme, lexeme + i + 2, len + 1);
	free(lexeme);
	free(exit_str);
	return (new_lexeme);
}

static int	process_env_variable(t_token *token, t_list *env_list, int i)
{
	int		start;
	int		end;
	char	*str_env;

	start = i;
	end = get_end(token->lexeme + i + 1);
	str_env = set_env(token->lexeme, start, end, env_list);
	if (str_env)
	{
		free(token->lexeme);
		token->lexeme = str_env;
		return (0);
	}
	return (i + 1);
}

void	scan_env(t_token *token, t_list *env_list)
{
	int		i;
	char	*new_lexeme;

	i = 0;
	while (token->lexeme[i])
	{
		if (token->lexeme[i] == '$')
		{
			if (token->lexeme[i + 1] == '\0' || token->lexeme[i + 1] == ' ')
				i++;
			else if (token->lexeme[i + 1] == '?')
			{
				new_lexeme = replace_exit_status(token->lexeme, i);
				if (!new_lexeme)
					return ;
				token->lexeme = new_lexeme;
				i++;
			}
			else
				i = process_env_variable(token, env_list, i);
		}
		else
			i++;
	}
}

void	env_expansion(t_list *env_list, t_scanner *scanner)
{
	t_token	*token;
	t_token	*prev_token;
	t_list	*tmp_tokens;

	prev_token = NULL;
	tmp_tokens = scanner->tokens;
	while (tmp_tokens)
	{
		token = (t_token *)tmp_tokens->content;
		if (token->type != SINGLE_QUOTED && !(prev_token && prev_token->type == HEREDOC))
			scan_env(token, env_list);
		prev_token = token;
		tmp_tokens = tmp_tokens->next;
	}
}

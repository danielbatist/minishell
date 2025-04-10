/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:46:52 by eteofilo          #+#    #+#             */
/*   Updated: 2025/04/09 20:21:52 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
static int	str_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] != c)
		i++;
	if (str[i] != c)
		i = -1;
	return (i);
}

static int	count_tokens(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '\"' && str_search(&tokens[i][1], '\"') == -1)
		{
			i++;
			while (tokens[i] && tokens[i][ft_strlen(tokens[i])] != '\"')
				i++;
		}
		count++;
		i++;
	}
	return (count);
}

static char	**get_tokens(char *input)
{
	char	**tokens;
	char	**filtered_tokens;
	char	*tmp;
	int		i;
	int		j;

	tokens = ft_split(input, ' ');
	filtered_tokens = (char **)malloc(sizeof(char *) * count_tokens(tokens));
	i = 0;
	j = 0;
	while (tokens[i])
	{
		filtered_tokens[j] = ft_strdup(tokens[i]);

		if (tokens[i][0] == '\"' && tokens[i][ft_strlen(tokens[i])] != '\"')
		{
			i++;
			while (tokens[i] && tokens[i][ft_strlen(tokens[i])] != '\"')
			{
				tmp = ft_strjoin(tmp, " ");
				tmp = ft_strjoin(tmp, tokens[i++]);
				printf("tmp: |%s|\n", tmp);
			}
			if (tokens[i])
				tmp = ft_strjoin(tmp, tokens[i]);
			printf("tmp: |%s|\n", tmp);
		}
		filtered_tokens[j++] = tmp;
		i++;
	}
	free_tokens(tokens);
	return (filtered_tokens);
}

static t_token_type	get_type(char *lexeme, int is_start)
{
	if (is_start)
		return(COMMAND);
	if (lexeme[0] == '|' && lexeme[1] == '\0')
		return(PIPE);
	if (lexeme[0] == '<' && lexeme[1] == '\0')
		return(REDIRECT_IN);
	if (lexeme[0] == '>' && lexeme[1] == '\0')
		return(REDIRECT_OUT);
	if (lexeme[0] == '<' && lexeme[1] == '<' && lexeme[2] == '\0')
		return(HEREDOC);
	if (lexeme[0] == '>' && lexeme[1] == '>' && lexeme[2] == '\0')
		return(APPEND);
	if (lexeme[0] == '\"' && lexeme[ft_strlen(lexeme) - 1] == '\"')
		return (DOUBLE_QUOTED);
	if (lexeme[0] == '\'' && lexeme[ft_strlen(lexeme) - 1] == '\'')
		return(SINGLE_QUOTED);
	if ((lexeme[0] == '\"' && lexeme[ft_strlen(lexeme) - 1] != '\"')
		|| (lexeme[0] == '\'' && lexeme[ft_strlen(lexeme) - 1] != '\''))
		return(UNCLOSED);
	return(PARAMETER);
}

t_list	*tokenizer(char *input)
{
	t_list	*tokens;
	t_token	*token;
	int		is_start;

	token = malloc(sizeof(t_token));
	tokens = NULL;
	is_start = 1;
	token->lexeme = ft_strtoken(input, ' ');
	while (token->lexeme)
	{
		token = NULL;
		token = malloc(sizeof(t_token));
		if (token->lexeme != NULL)
			token->type = get_type(token->lexeme, is_start);
		if (is_start++ == 1)
		{
			tokens = ft_lstnew(token);
		}
		else
		{
			ft_lstadd_back(&tokens, ft_lstnew(token));
		}
		token->lexeme = ft_strdup(ft_strtoken(NULL, ' '));
	}
	return (tokens);
}

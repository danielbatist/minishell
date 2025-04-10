/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:27:27 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/10 00:29:20 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	check_quotes_valid(const char *str)
{
	int	i;
	char	open_quotes;
	
	i = 0;
	open_quotes = '\0';
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
		{
			if (!open_quotes)
				open_quotes = str[i];
			else if (str[i] == open_quotes)
				open_quotes = '\0';
		}
		i++;
	}
	if (open_quotes)
	{
		printf("Error: Unclosed quotes\n");
		return (1);
	}
	return (0);
}



char	*ft_strtoken(const char *str, char delim)
{
	static char	*buffer_token;
	static char *next_token;
	char		*start;
	char		*token;
	int	 		in_quotes;
	char		quote_type;

	in_quotes = 0;
	quote_type = '\0';
	if (str)
	{
		free(buffer_token);
		buffer_token = ft_strdup(str);
		next_token = buffer_token;
	}
	if (!next_token ||*next_token == '\0')
	{
		free(buffer_token);
		buffer_token = NULL;
		return (NULL);
	}
	while (*next_token && *next_token == delim)
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	start = next_token;
	token = start;
	while (*next_token)
	{
		if ((*next_token == '\'' || *next_token == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote_type = *next_token;
		}
		else if (*next_token == quote_type && in_quotes)
				in_quotes = 0;
		else if (*next_token == delim && !in_quotes)
			break;
		next_token++;
	}
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;
	return (token);
}

int	main(void)
{
	char	*input;
	char 	*token;
	char	*token_clean;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("\nSaindo do minishell...\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (check_quotes_valid(input))
		{
			free(input);
			continue;
		}
		token = ft_strtoken(input, ' ');
		while (token)
		{
			token_clean = ft_strtrim(token, "\'\"");
			if (token_clean)
			{
				printf("Token: %s\n", token_clean);
				free(token_clean);
			}
			token = ft_strtoken(NULL, ' ');
		}
		free(input);
	}
	return (0);
}

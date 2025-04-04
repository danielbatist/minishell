/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:27:27 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/03 22:27:29 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

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
	start = next_token;
	while (*start && *start == delim)
		start++;
	if (*start == '\0')
		return (NULL);
	token = start;
	while (*next_token)
	{
		if (*next_token == '\"' || *next_token == '\'')
		{
			if (in_quotes == 0)
			{
				in_quotes = 1;
				quote_type = *next_token;
			}
			else if (*next_token == quote_type)
				in_quotes = 0;
		}
		else if (*next_token == delim && in_quotes == 0)
		{
			*next_token = '\0';
			next_token++;
			break;
		}
		next_token++;
	}
	return (token);
}

int	main(void)
{
	char	*input;
	char 	*token;

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
		token = ft_strtoken(input, ' ');
		while (token)
		{
			printf("Token: %s\n", token);
			token = ft_strtoken(NULL, ' ');
		}
		free(input);
	}
	return (0);
}

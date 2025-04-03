/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:51:42 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/03 20:48:49 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strtoken(const char *str, char delim)
{
	static char	*buffer_token;
	static char *next_token;
	char		*start;
	char		*token;

	if (str)
	{
		free(buffer_token);
		buffer_token = ft_strdup(str);
		next_token = buffer_token;
	}
	if (!next_token || next_token == '\0')
	{
		free(buffer_token);
		buffer_token = NULL;
		return (NULL);
	}
	start = next_token;
	while (*start && ft_strchr(*start, delim))
		start++;
	if (*start == '\0')
		return (NULL);
	token = start;
	while (*next_token && !ft_strchr(*next_token, delim))
		next_token++;
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}

int	main(void)
{
	char	*input;

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
		ft_strtoken(input, ' ');
		printf("Você digitou: %s\n", input);
		free(input);
	}
	return (0);
}

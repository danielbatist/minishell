/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:07:09 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/15 00:36:24 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

static void	handle_pipe_or_other(const char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			{
				printf("bash: syntax error near unexpected token 'newline'\n");
				return ;
			}
		}
		i++;
	}
}

int	handle_pipe(const char *input)
{
	int	i;
	int	len;

	if (!input)
		return (1);
	i = 0;
	len = strlen(input) - 1;
 	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
    handle_pipe_or_other(input);
	while (len > 0 && input[len] == ' ')
		len--;
	if (input[len] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
    return (0);
}

static int	handle_red_out(const char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			i++;
			if (input[i] == '>')
				return (0);
			while (input[i] == ' ')
				i++;
			if (input[i] == '|' || input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	handle_red_in(const char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<')
		{
			i++;
			if (input[i] == '<' || input[i] == '>')
				return (0);
			while (input[i] == ' ')
				i++;
			if (input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	handle_redirect(const char *input)
{
	int	i;
	int	len;

	if (!input)
		return (1);
	i = 0;
	len = strlen(input) - 1;
 	while (input[i] == ' ')
		i++;
	if (input[i] == '>' || input[i] == '<')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (handle_red_out(input))
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (handle_red_in(input))
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	while (len > 0 && input[len] == ' ')
		len--;
	if (input[len] == '>' || input[len] == '<')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
    return (0);
}

int main (int argc, char **argv)
{
    int i = 1;
    while (i < argc)
    {
        if (handle_pipe(argv[i]))
			return (1);
		handle_redirect(argv[i]);
        printf("teste handle pipe: %s\n", argv[i]);
        i++;
    }
    return (0);
}

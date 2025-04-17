/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:07:09 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/16 20:59:15 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../inc/minishell.h"

char	*extrac_filename(const char *input)
{
	int				i;
	int				len;
	unsigned int	start;

	if (!input)
		return (NULL);
	i = 0;
	while (input[i] == ' ')
		i++;
	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '|' \
	&& input[i] != '<' && input[i] != '>')
		i++;
	len = i - start;
	return (ft_substr(input, start, len));
}

int	redirect_int(const char *input)
{
	int		i;
	char	*filename;

	i = 1;
	if (input[i] == '<')
		i++;
	while (input[i] == ' ')
		i++;
	filename = extrac_filename(input);
	printf("teste filename: %s\n", filename);
	return (0);
}

/*int	redirect_out(const char *input)
{

}*/
int	handle_redirect(const char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '<')
		return (redirect_in(input + i));
	/*if (input[i] == '>')
		return (redirect_out(input + i));*/
}

int	print_error(char c)
{
	if (c == '\0' || c == ' ')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else
	{
		printf("bash: syntax error near unexpected token `%c'\n", c);
		return (1);
	}
	return (0);
}

int	handle_pipe(const char *input)
{
	int	i;

	if (!input)
		return (1);
	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (print_error(input[i]));
	i = 0;
	while (input[i])
	{	
		if (input[i] == '|' && input[i + 1] == '|')
			return (print_error(input[i + 1]));
		if (input[i] == '|' && input[i + 1] == '\0')
			return (print_error(input[i + 1]));
		i++;
	}
	return (0);
}


int	main (int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (handle_pipe(argv[i]))
			return (1);
		if (handle_redirect(argv[i]))
			return (1);
		printf("teste handle pipe: %s\n", argv[i]);
		i++;
	}
	return (0);
}

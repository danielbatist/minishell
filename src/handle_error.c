/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:02:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/14 23:39:20 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// Error de  > no final da string /
// Error de > > espaço entre redirect
// Error de  >> > ou >>> e < << ou <<< mais de redirect em append ou heredoc


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

int	handle_error(const char *input)
{
	if (handle_pipe(input))
		return (1);
	if (handle_redirect(input))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:12:16 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/16 20:10:27 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*extrac_filename(const char *input)
{
	int				i;
	int				len;
	unsigned int	start;
	char			*str;

	if (!input)
		return (1);
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

void	print_error(char c)
{
	if (c == '\0' || c == ' ')
		printf("bash: syntax error near unexpected token `newline'\n");
	else
		printf("bash: syntax error near unexpected token `%c'\n", c);
}

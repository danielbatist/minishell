/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:14:47 by eteofilo          #+#    #+#             */
/*   Updated: 2025/04/18 06:24:47 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tokens_len(t_scanner *scanner)
{
	t_list	*tmp;
	int		i;

	tmp = scanner->tokens;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*concat_token(t_scanner *scanner)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ((t_token *)(scanner->tokens->content))->lexeme;
	tmp2 = ((t_token *)(scanner->tokens->next->content))->lexeme;
	str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (str);
}

t_command	*parser(char *input, t_list *env_list)
{
	t_scanner	*scanner;
	int			is_start;
	int			i;
	int			j;
	int			tokens_l;
	t_command	*complex_command;

	is_start = 0;
	i = -1;
	j = 0;
	scanner = init_scanner(input);
	scan_tokens(scanner);
	env_expansion(env_list, scanner);
	printf("line: %i\n", scanner->line);
	complex_command = (t_command *)malloc(sizeof(t_command) * scanner->line);
	while (scanner && scanner->tokens)
	{
		if(is_start == 0)
		{
			tokens_l = tokens_len(scanner);
			i++;
			complex_command[i].simple_command = (char **)malloc(sizeof(char *) * tokens_l);
		}
		if (((t_token *)(scanner->tokens->content))->plus == TRUE)
			complex_command[i].simple_command[j] = concat_token(scanner);
		else
			complex_command[i].simple_command[j] = ((t_token *)(scanner->tokens->content))->lexeme;

		scanner->tokens = scanner->tokens->next;
		j++;
		is_start++;
		if (((t_token *)(scanner->tokens->content))->type == PIPE)
			is_start = 0;
		printf("AQUI!\n");

	}
	return(complex_command);
}

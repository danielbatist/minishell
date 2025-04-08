/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/08 16:48:35 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft.h"

typedef enum e_token_type {
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	COMMAND,
	PARAMETER,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	UNCLOSED,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
}	t_token;

t_list	*tokenizer(char *input);

#endif

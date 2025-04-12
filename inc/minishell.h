/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/11 20:10:56 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft.h"

typedef enum e_token_type
{
	COMMAND,
	FLAG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	TARGET,
	PARAMETER,
	SINGLE_QUOTED = 39,
	DOUBLE_QUOTED = 34,
	UNCLOSED,
	EOF_TOKEN
}	t_token_type;

typedef enum e_is_command
{
	FALSE,
	TRUE,
	REDIRECT
}	t_is_command;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
}	t_token;
typedef struct s_scanner
{
	int				start;
	int				current;
	t_is_command	is_command;
	int				line;
	char			*src;
	t_list			*tokens;
}	t_scanner;


t_list	*tokenizer(char *input);
int		handle_error(t_list *tokens);

#endif

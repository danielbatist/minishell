/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/22 12:10:09 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

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
}					t_token_type;

typedef enum e_is_command
{
	FALSE,
	TRUE,
	REDIRECT
}					t_is_command;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
}					t_token;
typedef struct s_scanner
{
	int				start;
	int				current;
	t_is_command	is_command;
	int				line;
	char			*src;
	t_list			*tokens;
}					t_scanner;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

void		scan_tokens(t_scanner *scanner);
t_scanner	*init_scanner(char *input);
void		add_token(t_scanner *scanner, t_token_type token_type);
void		add_str_token(t_scanner *scanner, t_token_type token_type);
void		add_multichar_token(t_scanner *scanner, t_token_type token_type);
int			handle_error(t_list *tokens);
int			print_error(t_token *token);
int			handle_redirect(t_list *tokens);
int			check_redirect_end(t_token *token);
int			check_redirects(t_token *token, t_token *next);
int			check_redirect_out(t_token *token, t_token *next);
int			check_redirect_in(t_token *token, t_token *next);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/04/18 06:25:33 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

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
	t_is_command	plus;
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

typedef struct s_commands
{
	char **simple_command;
	int		fd_in;
	int		fd_out;
}	t_command;

void				scan_tokens(t_scanner *scanner);
t_scanner			*init_scanner(char *input);
void				add_token(t_scanner *scanner, t_token_type token_type);
void				add_str_token(t_scanner *scanner, t_token_type token_type);
void				add_multichar_token(t_scanner *scanner,
						t_token_type token_type);
int					handle_error(t_list *tokens);
t_list				*catch_env(char **envp);
void				env_expansion(t_list *env_list, t_scanner *scanner);
t_command			*parser(char *input, t_list *env_list);

#endif

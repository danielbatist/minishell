/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/15 20:41:23 by dbatista         ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

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
	char			*lexeme;
	t_token_type	type;
	t_is_command	plus;
	t_is_command	has_space;
}					t_token;
typedef struct s_scanner
{
	int				start;
	int				current;
	t_is_command	is_command;
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
	char	**simple_command;
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	char	*append_file;
	char	*heredoc_delim;
}	t_command;

//token
void				add_token(t_scanner *scanner, t_token_type token_type);
void				add_str_token(t_scanner *scanner, t_token_type token_type);
void				add_multichar_token(t_scanner *scanner, t_token_type token_type);
char				*get_token_type(int type);
int					tokens_len(t_scanner *scanner);
//scanner
t_scanner			*init_scanner(char *input);
void				scan_tokens(t_scanner *scanner);

//free
void				free_token(void *content);
void				free_scanner(t_scanner *scanner);
void				free_env_list(t_list *env_list);
void				free_complex_command(t_command *cmds);
t_command			*free_and_return(t_scanner *scanner);

//print
int					print_error(t_token *token);
void				print_token_list(t_list *tokens);
void				print_commands(t_command *cmd);

//redirects
void				redirects_token(t_list **token_list);
void				handle_redirects(t_list *start, t_command *cmd);
int					apply_redirect(t_command *cmd);

//execution
void				execute_command(t_command *cmd);

//utils
int					is_redirect(t_token_type type);
int					handle_error(t_list *tokens);
int					is_flag(t_scanner *scanner, char *s);
int					is_metachar(t_token_type type);
int					check_redirect_in(t_token *token, t_token *next);
int					check_redirect_out(t_token *token, t_token *next);
int					check_redirects(t_token *token, t_token *next);
void				set_signal(void);
void				env_expansion(t_list *env_list, t_scanner *scanner);
char				**extract_simple_cmd(t_list **token_list);
t_list				*catch_env(char **envp);
t_command			*parser(char *input, t_list *env_list);

#endif

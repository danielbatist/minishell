/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/05/25 22:53:52 by dbatista         ###   ########.fr       */
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
	REDIRECT,
	FILE_NOT_FOUND,
	IS_DIR,
	PERM_DENIED
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
	char			**simple_command;
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	char			*append_file;
	char			*heredoc_delim;
	char			*heredoc_file;
	t_is_command	error_flag;
	t_is_command	heredoc_quoted;
	t_is_command	is_heredoc;
}	t_command;

//token
void		add_token(t_scanner *scanner, t_token_type token_type);
void		add_str_token(t_scanner *scanner, t_token_type token_type);
void		add_multichar_token(t_scanner *scanner, t_token_type token_type);
char		*get_token_type(int type);
int			tokens_len(t_scanner *scanner);
//scanner
t_scanner	*init_scanner(char *input);
void		scan_tokens(t_scanner *scanner);

//free
void		free_token(void *content);
void		free_scanner(t_scanner *scanner);
void		free_env_list(t_list *env_list);
void		free_complex_command(t_command *cmds);
t_command	*free_and_return(t_scanner *scanner);

//print
int			print_error(t_token *token);
int			print_error_direc_and_file(char *lexeme, t_is_command flag);
void		print_token_list(t_list *tokens);
void		print_commands(t_command *cmd);

//redirects
void		clean_heredoc(t_command *cmd);
void		redirects_token(t_list **token_list);
int			handle_redirects(t_list *start, t_command *cmd, t_list *env_list);
int			handle_redirect_file(t_token *token, t_token *next_token, t_command *cmd);
int			handle_redirect_heredoc(t_token *token, t_token *next_token, t_command *cmd, t_list *env_list);
int			handle_heredoc(t_command *cmd, char **out_file, t_token *next, t_list *env_list);
int			open_redirect(t_command *cmd);
int			open_infile(char *infile);
int			open_outfile(char *outfile);
int			open_append(char *append);
int			open_herefile(char *heredoc);
char		*create_tmp_file(void);
char		*here_exp(char *line, t_list *env_list);
int			open_heredoc(t_command *cmd, char *delim, char *tmp_filename, t_list *env_list);
int			validate_file(t_token *token, char *lexeme);
void		dup_redirect(t_command *cmd);

//execution
void	execute_command(t_command *cmd, t_list *env_list);
char	**get_envp(t_list *env_list);
char	*get_path(char *cmd, t_list *env_list);
void	free_paths(char **paths);

//env
void		env_expansion(t_list *env_list, t_scanner *scanner);
t_list		*catch_env(char **envp);
int			get_end(char *str);
char		*set_env(char *str, int start, int end, t_list *env_list);
char		*search_env(char *str, t_list *env_list);
char		*join_replacement(char *str, int start, int end, char *env_value);
char		*search_env(char *str, t_list *env_list);

//utils
int			is_redirect(t_token_type type);
int			handle_error(t_list *tokens);
int			is_flag(t_scanner *scanner, char *s);
int			is_metachar(t_token_type type);
int			check_redirect_in(t_token *token, t_token *next);
int			check_redirect_out(t_token *token, t_token *next);
int			check_redirects(t_token *token, t_token *next);
void		set_signal(void);
char		**extract_simple_cmd(t_list **token_list);
t_command	*parser(char *input, t_list *env_list);

#endif

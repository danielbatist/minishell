/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:41 by dbatista          #+#    #+#             */
/*   Updated: 2025/06/11 20:22:37 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../lib/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

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
	NOT_IS_DIR,
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

typedef struct s_pipefd
{
	int	fd[2];
}	t_pipefd;

typedef struct s_exec
{
	int			is_pipe;
	int			is_builtin;
	t_pipefd	*pipefd;
	pid_t		*pids;
}	t_exec;

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
	t_list			*env_list;
	t_exec			*data;
}	t_command;

//token
void		add_token(t_scanner *scanner, t_token_type token_type);
void		add_str_token(t_scanner *scanner, t_token_type token_type);
void		add_multichar_token(t_scanner *scanner, t_token_type token_type);
char		*get_token_type(int type);

//scanner
t_scanner	*init_scanner(char *input);
void		scan_tokens(t_scanner *scanner);

//free
void		free_env(t_env **env);
void		free_list_and_env(t_list *tmp_list, t_env *env);
void		free_token(void *content);
void		free_scanner(t_scanner *scanner);
void		free_env_list(t_list *env_list);
void		free_complex_command(t_command *cmds);
t_command	*free_and_return(t_scanner *scanner);
void		free_exec(char **exec);
void		free_pipes(t_pipefd *pipefd, int n_of_pipes);
void		free_env(t_env **env);
void		free_list_and_env(t_list *tmp_list, t_env *env);
void		free_child_not_found(char *path, char **envp,
				t_command *cmd, int *i);

//print
int			print_error(t_token *token);
int			print_error_direc_and_file(char *lexeme, t_is_command flag);
void		print_dot_error(char *lexeme);
void		print_commands(t_command *cmd);
void		print_token_list(t_list *tokens);
void		print_dot_error(char *lexeme);

//redirects
void		clean_heredoc(t_command *cmd);
void		redirects_token(t_list **token_list);
int			handle_redirects(t_list *start, t_command *cmd, t_scanner *scanner);
int			handle_redirect_file(t_token *token, t_token *next_token,
				t_command *cmd);
int			handle_redirect_heredoc(t_token *token, t_token *next_token,
				t_command *cmd, t_scanner *scanner);
int			handle_heredoc(t_command *cmd, char **out_file,
				t_token *next, t_scanner *scanner);
int			open_redirect(t_command *cmd);
int			open_infile(char *infile);
int			open_outfile(char *outfile);
int			open_append(char *append);
int			open_herefile(char *heredoc);
char		*create_tmp_file(void);
char		*here_exp(char *line, t_list *env_list);
int			open_heredoc(t_command *cmd, char *delim, char *tmp_filename);
int			validate_file(t_token *token, char *lexeme);
void		dup2_redirect(t_command *cmd);

//pipe
int			get_pipefd(t_command *complex_command, t_pipefd **pipefd);

//main
int			main(int ac, char **av, char **envp);
t_command	*input_and_parser(char *input, t_list *env_list);
void		process_input(char *input, t_list *env_list);
void		handle_exit(char *input, t_list *env_list);
t_exec		*init_exec_data(t_command *cmd);

//signal
void		handle_sig_readline(int sig);
void		handle_sig_exec(int sig);
void		set_signal_readline(void);
void		set_signal_exec_parent(void);
void		set_signal_child(void);

//builtins
int			ft_cd(char **cmd, t_list *env_list);
int			ft_echo(char **cmd);
int			ft_env(t_list *env_list);
int			ft_export(char **cmd, t_list *env_list);
int			ft_pwd(void);
int			ft_unset(t_command *cmd);
int			ft_exit(t_command *cmd);
int			is_builtins(char *str);
int			exec_builtins(t_command *cmd);

//execution
void		execute_child(t_command *cmd, int i, int is_pipe, t_pipefd *pipefd);
int			execute_builtins_in_parent(t_command *cmd, t_exec *data, int *i);
void		execute_parent(t_exec *data);
void		execute_commands(t_command *cmd, t_exec *data, t_list *env_list);
char		*search_in_path(char *cmd, char *path_var);
char		*get_path(char *cmd, t_list *env_list);
char		**get_envp(t_list *env_list);
char		*get_env_value(t_list *env_list, const char *name);
void		close_pipes(t_pipefd *pipefd, int n_of_pipes);
void		dup2_pipes(t_pipefd *pipefd, int is_pipe, int *i);

//env
void		env_expansion(t_list *env_list, t_scanner *scanner);
t_list		*catch_env(char **envp);
int			get_end(char *str);
char		*set_env(char *str, int start, int end, t_list *env_list);
char		*search_env(char *str, t_list *env_list);
char		*join_replacement(char *str, int start, int end, char *env_value);
char		*search_env(char *str, t_list *env_list);

//utils
void		set_exit_status(int status);
int			check_error_flag(t_command *cmd, int *i);
int			*get_exit_status(void);
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

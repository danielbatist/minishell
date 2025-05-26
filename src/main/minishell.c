/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/05/23 14:31:57 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_exit(char *input, t_list *env_list)
{
	printf("exit\n");
	if (input)
		free(input);
	redirects_token(&env_list);
	exit(0);
}

static void	process_input(char *input, t_list *env_list)
{
	t_command	*complex_command;
	int			i;
	int			j;
	t_pipefd	*pipefd;
	int			is_pipe;
	pid_t		*pids;
	int			is_builtin = FALSE;

	if (*input)
		add_history(input);
	complex_command = parser(input, env_list);
	if (!complex_command)
		return ;
	i = 0;
	is_pipe = get_pipefd(complex_command, &pipefd);
	pids = malloc(sizeof(pid_t) * (is_pipe + 1));
	while (complex_command[i].simple_command)
	{
		if (complex_command[i].error_flag)
		{
			clean_heredoc(&complex_command[i]);
			i++;
			continue ;
		}
		if (is_pipe > 0 || !is_builtin)
		{
			pids[i] = fork();
			if (pids[i] == 0)
			{
				if (i > 0 && is_pipe > 0)
					dup2(pipefd[i - 1].fd[0], STDIN_FILENO);
				if (i < is_pipe)
					dup2(pipefd[i].fd[1], STDOUT_FILENO);
				int j = 0;
				while (j < is_pipe && is_pipe > 0)
				{
					close(pipefd[j].fd[0]);
					close(pipefd[j].fd[1]);
					j++;
				}
				if (open_redirect(&complex_command[i]) < 0)
					exit (1);
				dup_redirect(&complex_command[i]);
				if (complex_command[i].simple_command && &complex_command[i].simple_command[0])
				{
					ft_printf_fd(2, "Executando: %s\n", complex_command[i].simple_command[0]);
					execvp(complex_command[i].simple_command[0], complex_command[i].simple_command);
				}
				ft_printf_fd(2, "minishell: Erro ao executar o comando: %s\n", complex_command[i].simple_command[0]);
				exit(1);
			}
			else
			{
				//wait(NULL);
				clean_heredoc(complex_command);
				//j = 0;
				// Fechar apenas as extremidades não usadas dos pipes
				if (i > 0)
					close(pipefd[i-1].fd[0]);
				if (i < is_pipe)
					close(pipefd[i].fd[1]);
				j = 0;
				while (j <= is_pipe)
				{
					waitpid(pids[j], NULL, 0);
					j++;
				}
			}
			i++;
		}
		//execute_external_command(&complex_command[i++]);
	}
	//free(pipefd);
	//free(pids);
	print_commands(complex_command);
	free_complex_command(complex_command);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_list		*env_list;

	(void)ac;
	(void)av;
	env_list = catch_env(envp);
	while (1)
	{
		set_signal();
		input = readline("minishell> ");
		if (!input)
			handle_exit(NULL, env_list);
		process_input(input, env_list);
		free(input);
	}
	return (0);
}

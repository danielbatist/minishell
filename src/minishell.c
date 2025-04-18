/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:40 by eteofilo          #+#    #+#             */
/*   Updated: 2025/04/18 06:07:50 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void del(void * content)
{
	t_token	*token = (t_token *)content;
	free(token->lexeme);
	free(content);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	//t_scanner	*scanner;
	char		***complex_command;
	//t_list		*tmp_tokens;
	t_list		*env_list;
	//t_list		*tmp_env;
	//char	*token_clean;

	(void)ac;
	(void)av;
	env_list = catch_env(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			free(input);
			printf("\nSaindo do minishell...\n");
			break ;
		}
		if (*input)
			add_history(input);
		complex_command = parser(input, env_list);

		// scanner = init_scanner(input);
		// scan_tokens(scanner);
		// env_expansion(env_list, scanner);
		// if (handle_error(scanner->tokens))
		// {
		// 	free(input);
		// 	rl_clear_history();
		// 	continue;
		// }
		// tmp_tokens = scanner->tokens;
		// tmp_env = env_list;
		while (complex_command)
		{
			while (*complex_command)
				printf("%s ", **complex_command++);
			printf("\n");
			complex_command++;
			// if (((t_token *)(scanner->tokens->content))->lexeme[0] == 'E')
			// {
			// 	while (tmp_env)
			// 	{
			// 		printf("%s | %s\n", ((t_env *)(tmp_env->content))->name, ((t_env *)(tmp_env->content))->value);
			// 		tmp_env = tmp_env->next;
			// 	}
			// }
			// if (((t_token *)(scanner->tokens->content))->type == COMMAND)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "COMMAND");
			// if (((t_token *)(scanner->tokens->content))->type == PARAMETER)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "PARAMETER");
			// if (((t_token *)(scanner->tokens->content))->type == FLAG)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "FLAG");
			// if (((t_token *)(scanner->tokens->content))->type == PIPE)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "PIPE");
			// if (((t_token *)(scanner->tokens->content))->type == REDIRECT_IN)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "REDIRECT_IN");
			// if (((t_token *)(scanner->tokens->content))->type == REDIRECT_OUT)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "REDIRECT_OUT");
			// if (((t_token *)(scanner->tokens->content))->type == HEREDOC)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "HEREDOC");
			// if (((t_token *)(scanner->tokens->content))->type == APPEND)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "APPEND");
			// if (((t_token *)(scanner->tokens->content))->type == TARGET)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "TARGET");
			// if (((t_token *)(scanner->tokens->content))->type == SINGLE_QUOTED)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "SINGLE_QUOTED");
			// if (((t_token *)(scanner->tokens->content))->type == DOUBLE_QUOTED)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "DOUBLE_QUOTED");
			// if (((t_token *)(scanner->tokens->content))->type == UNCLOSED)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "UNCLOSED");
			// if (((t_token *)(scanner->tokens->content))->type == EOF_TOKEN)
			// 	printf("Token: %s \nType: %s\n ------------------\n", ((t_token *)(scanner->tokens->content))->lexeme, "EOF_TOKEN");
			// scanner->tokens = scanner->tokens->next;
		}
		// scanner->tokens = tmp_tokens;
		free(input);
		// ft_lstclear(&scanner->tokens, del);
		//free(scanner->tokens);
		// free(scanner);
	}
	return (0);
}

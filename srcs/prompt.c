/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:14:47 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/05 18:10:44 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	salopeva(int x)
{
	if (x == SIGINT)
		printf("tié une belle salope vaa");
	else
		printf("tié un chien");
}

int	prompt(char **envp)
{
	char	*input;
	t_token *tokens;
	t_cmd	*ast;
	t_shell	*shell;

	shell = init_shell_data(envp);
	input = NULL;
	// pid_t	wpid;
	// int		status;
	while (1)
	{
		//signal(SIGINT, &salopeva);
		input = readline("Minishell$ ");
		fprintf(stdout, "---%s---\n", input);
		// printf("after while(0)\n");
		// printf("after while(1)\n");
		if (!input)
		{
			// ft_putstr_fd("fdp", 1);
			//exit (1);
			break ;
		}
		else
		{
			// printf("after while(2)\n");
			tokens = init_tokens(input);
			// printf("NEW       TOKEN      TYPE\n");
			//print_tokens(tokens);
			syntax_checker(tokens);
			ast = create_ast(tokens, shell);
			//printf("AST DONE %p!\n", ast);
			//executor_print(ast);
			executor(ast);
			// close(ast->infile);
			// close(ast->outfile);
			// close(ast->shell->pipefd[0]);
			// close(ast->shell->pipefd[1]);
			// while (wpid > 0)
			// 	wpid = wait(&status);
			free_token(tokens);
			ast_free(ast);
		}
		// printf("after while(3)\n");
		add_history(input);
		free(input);
		input = NULL;
		// printf("after while(4)\n");
	}
	return (0);
}
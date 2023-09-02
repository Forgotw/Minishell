/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:14:47 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 17:52:43 by lsohler          ###   ########.fr       */
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
	char	*input = NULL;
	t_token *tokens;
	t_cmd	*ast;
	while (1)
	{
		signal(SIGINT, &salopeva);
		input = readline("Minishell$ ");
		if (!input)
			exit (1);
		else
		{
			tokens = init_tokens(input);
			printf("NEW       TOKEN      TYPE\n");
			print_tokens(tokens);
			syntax_checker(tokens);
			ast = create_ast(tokens, envp);
			printf("AST DONE %p!\n", ast);
			//executor_print(ast);
			executor(ast);
			free_token(tokens);
			ast_free(ast);
		}
		add_history(input);
		if (!ft_strncmp(input, "exit", 4))
			exit (0);
	}
}
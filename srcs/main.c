/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:12:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/30 14:23:44 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tmp)
{
	// t_token *tmp;

	// tmp = tokens;
	if (!tmp)
		exit (printf("NO TOKENS\n"));
	while (tmp)
	{
		if (!tmp)
			printf("    TOKENS ERROR\n");
		//printf("TOKEN ADRESS: %p\n", tmp);
		printf("Token_type: %i | Word: $%s$\n", tmp->type, tmp->str);
		printf("token join: %i\n", tmp->join);
		//printf("Str adress: %p\n", tmp->str);
		tmp = tmp->next;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->str)
			free(token->str);
		free(token);
		token = tmp;
	}
}
/*
int	main(int ac, char **av, char **envp)
{
	int		ret;
	t_shell	*shell;
	int		i;
	pid_t	pid;
	

	(void)ac;
	shell = malloc(sizeof(t_shell));
	shell->env = ft_arrdup(envp);
	ret = 0;
	i = 1;
	int	count = 0;
	while (av[i])
	{
		pid = fork();
		if (pid == 0)
		{
			shell->env = array_add_str(shell->env, av[i]);
			printf("CHILD count: %i i:%i\n", count, i);
			//printf("\n\nADDING TO ENV\n\n");
			//print_export(shell->env);
			count++;
			exit (0);
		}
		else
			printf("PARENT count: %i i: %i\n", count, i);
		i++;
		//waitpid(pid, NULL, 0);
	}
	//print_export(shell->env);
	//ft_putstr_fd("\nTEST 2\n", 1);
	//array_add_str(shell->env, ft_strdup(av[1]));
	//printf("\n\n\nCOUCOU\n\n\n");
	waitpid(pid, NULL, 0);
	printf("\n\n\n AFTER FORK\n\n\n");
	print_export(shell->env);
	// if (ac < 2)
	// 	return (printf("ARGUMENTS COUNT ERROR\n"));
	// if (!ft_strcmp(av[1], "export"))
	// {
	// 	ret = export(&av[1], shell);
	// 	print_export(shell->env);
	// 	return (printf("RETURN VALUE OF EXPORT: %i\n", ret));
	// }
	// else if (!ft_strcmp(av[1], "unset"))
	// {
	// 	ret = unset(&av[1], shell);
	// 	print_export(shell->env);
	// 	return (printf("RETURN VALUE OF EXPORT: %i\n", ret));
	// }
	return (0);
}*/

int	main(int ac, char **av, char **envp)
{
	t_token *tokens;
	t_cmd	*ast;

	(void)envp;
	if (ac != 2)
		//return (printf("argument error\n"));
		return (1);
	ret_status = 0;
	tokens = init_tokens(av[1]);
	printf("NEW       TOKEN      TYPE\n");
	print_tokens(tokens);
	syntax_checker(tokens);
	ast = create_ast(tokens);
	printf("AST DONE %p!\n", ast);
	executor_print(ast);
	free_token(tokens);
	ast_free(ast);
}

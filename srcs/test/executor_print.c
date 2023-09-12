/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:10 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 20:07:18 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*execute_subshell_print(t_cmd *ast)
{
	printf("     \033[31;1m----- ON SUBSHELL ------\n");
	print_cmd(ast, "     ");
	printf("\033[0m\n\n\n");
	while (ast->subshell)
	{
		printf("\n\033[33;1m-------------Descending------------\033[0m\n\n\n");
		ast = ast->subshell;
		if (ast->type == SUBSHELL)
		{
			printf("     \033[31;1m----- ON SUBSHELL ------\n");
			print_cmd(ast, "     ");
			printf("\033[0m\n\n\n");
		}
	}
	return (ast);
}

void	pre_execute_cmd_print(t_cmd *ast)
{
	if (ast->tok)
	{
		ast->tok = expand_token(ast->tok, ast->shell);
		ast->cmd = create_cmd_array(ast->tok);
	}
	if (ast->redir)
	{
		ast->redir = expand_token(ast->redir, ast->shell);
		ast->redir = join_redir_token(ast->redir);
	}
}

t_cmd	*execute_cmd_print(t_cmd *ast)
{
	pre_execute_cmd_print(ast);
	print_cmd(ast, "            \033[37;1m");
	printf("\033[0m");
	if (ast->next)
	{
		printf("\n\033[32;1m            =======Going next======\033[0m\n\n\n");
		ast = ast->next;
	}
	else
	{
		while (ast)
		{
			ast = ast->upshell;
			printf("\n\033[34;1m++++++++++++++++Going up++++++++++++++\033[0m\n\n\n");
			if (ast && ast->next)
			{
				printf("     \033[31;1m----- ON SUBSHELL ------\n");
				print_cmd(ast, "     ");
				printf("\n\n\033[36;1m===========Going next==========\033[0m\n\n\n");
				ast = ast->next;
				break ;
			}
		}
	}
	return (ast);
}

int	executor_print(t_cmd *ast)
{
	printf("\n\n\n\n");
	while (ast)
	{
		if (ast->type == SUBSHELL)
			ast = execute_subshell_print(ast);
		else if (ast->type == CMD || ast->type == 0)
			ast = execute_cmd_print(ast);
	}
	printf("   OOOOO finish executor OOOOO\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:17:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/05 18:20:53 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Si on est sur une commande next = subshell ast = next */
/* Si on est sur un subshell subshell = new upshell = ast et ast = subshell */
/* Si on est sur NULL, ast = new type = subshell upshell = NULL*/
/* Creer une struct subshell et descend */
t_cmd	*create_subshell(t_token **token, t_cmd *ast, t_shell *shell)
{
	//printf("THIS IS A SUBSHELL\n");
	if (ast == NULL)
	{
		printf("          CREATING SUBSHELL ON null\n");
		ast = new_cmd(SUBSHELL, shell);
	}
	else if (ast->type == CMD)
	{
		printf("          CREATING SUBSHELL ON next\n");
		ast->next = new_cmd(SUBSHELL, shell);
		ast->next->upshell = ast->upshell;
		ast = ast->next;
	}
	else if (ast->type == SUBSHELL)
	{
		printf("          CREATING SUBSHELL ON subshell\n");
		ast->subshell = new_cmd(SUBSHELL, shell);
		ast->subshell->upshell = ast;
		ast = ast->subshell;
	}
	else if (ast->type == 0)
		ast->type = SUBSHELL;
	printf("          \033[31;1mSUBSHELL ADD: %p\n", ast);
	*token = (*token)->next;
	return (ast);
}

t_cmd	*close_subshell(t_token **token, t_cmd *ast)
{
	if (ast->cmd)
	{
		printf("          WE ARE AT: ");
		print_array(ast->cmd);
	}
	else
		printf("          WE ARE AT: add: %p\n", ast->cmd);
	ast = ast->upshell;
	*token = (*token)->next;
	if (ast && ast->cmd)
	{
		printf("                 BACK TO ADD: %p\n", ast);
		printf("                 BACK TO: ");
		print_array(ast->cmd);
	}
	else if (ast)
		printf("                 BACK TO: add: %p\n", ast->cmd);
	else if (!ast)
		printf("                    THERE IS NO AST !!!\n");
	return (ast);
}

t_shell	*init_shell_data(char **envp)
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	shell->env = ft_arrdup(envp);
	shell->status = 0;
	shell->prev_pipe_in = -1;
	return (shell);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:22:02 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/08 13:31:32 by lsohler          ###   ########.fr       */
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
		// printf("          CREATING SUBSHELL ON null\n");
		ast = new_cmd(SUBSHELL, shell);
	}
	else if (ast->type == CMD)
	{
		// printf("          CREATING SUBSHELL ON next\n");
		// ast->next = new_cmd(SUBSHELL, shell);
		// ast->next->upshell = ast->upshell;
		// ast = ast->next;
		ast = create_node_on_next(SUBSHELL, shell, ast);
	}
	else if (ast->type == SUBSHELL)
	{
		// printf("          CREATING SUBSHELL ON subshell\n");
		// ast->subshell = new_cmd(SUBSHELL, shell);
		// ast->subshell->upshell = ast;
		// ast = ast->subshell;
		ast = create_node_on_subshell(SUBSHELL, shell, ast);
	}
	else if (ast->type == 0)
		ast->type = SUBSHELL;
	// printf("          \033[31;1mSUBSHELL ADD: %p\n", ast);
	*token = (*token)->next;
	return (ast);
}

t_cmd	*close_subshell(t_token **token, t_cmd *ast)
{
	// if (ast->cmd)
	// {
	// 	// printf("          WE ARE AT: ");
	// 	print_array(ast->cmd);
	// }
	// else
	// 	// printf("          WE ARE AT: add: %p\n", ast->cmd);
	ast = ast->upshell;
	*token = (*token)->next;
	// if (ast && ast->cmd)
	// {
	// 	// printf("                 BACK TO ADD: %p\n", ast);
	// 	// printf("                 BACK TO: ");
	// 	print_array(ast->cmd);
	// }
	// else if (ast)
	// 	printf("                 BACK TO: add: %p\n", ast->cmd);
	// else if (!ast)
	// 	printf("                    THERE IS NO AST !!!\n");
	return (ast);
}
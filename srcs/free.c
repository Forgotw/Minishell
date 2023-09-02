/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:04:51 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 13:21:51 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *ast)
{
	printf("                          \033[31;1mFree: %p\n\033[0m", ast);
	if (!ast)
		return ;
	if (ast->cmd)
		free_array(ast->cmd);
	if (ast->path)
		free(ast->path);
	if (ast->tok)
		free_token(ast->tok);
	if (ast->redir)
		free_token(ast->redir);
	free(ast);
}

t_cmd	*navigate_subshell(t_cmd *ast)
{
	while (ast->subshell)
	{
		ast = ast->subshell;
	}
	return (ast);
}

t_cmd	*backward_and_free_cmd(t_cmd *ast)
{
	t_cmd	*tmp;

	while (ast)
	{
		tmp = ast;
		ast = ast->upshell;
		free_cmd(tmp);
		if (ast && ast->next)
		{
		tmp = ast;
			ast = ast->next;
			free_cmd(tmp);
			break ;
		}
		if (ast && ast->subshell)
			free_cmd(ast->subshell);
	}
	return (ast);
}

t_cmd	*navigate_cmd(t_cmd *ast)
{
	t_cmd	*tmp;

	if (ast->next)
	{
		tmp = ast;
		ast = ast->next;
		free_cmd(tmp);
	}
	else
		ast = backward_and_free_cmd(ast);
	return (ast);
}

int	ast_free(t_cmd *ast)
{
	printf("\n\n\n\n");
	if (ast && ast->shell)
	{
		free_array(ast->shell->env);
		free(ast->shell);
	}
	while (ast)
	{
		if (ast->type == SUBSHELL)
			ast = navigate_subshell(ast);
		else if (ast->type == CMD || ast->type == 0)
			ast = navigate_cmd(ast);
	}
	printf("   OOOOO finish free OOOOO\n");
	return (0);
}

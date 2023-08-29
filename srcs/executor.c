/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 17:18:48 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*execute_subshell(t_cmd *ast)
{
	while (ast->subshell)
	{
		ast = ast->subshell;
	}
	return (ast);
}

t_cmd	*execute_cmd(t_cmd *ast)
{
	if (ast->next)
	{
		ast = ast->next;
	}
	else
	{
		while (ast)
		{
			ast = ast->upshell;
			if (ast && ast->next)
			{
				ast = ast->next;
				break ;
			}
		}
	}
	return (ast);
}

int	executor(t_cmd *ast)
{
	while (ast)
	{
		if (ast->type == SUBSHELL)
			ast = execute_subshell(ast);
		else if (ast->type == CMD || ast->type == 0)
			ast = execute_cmd(ast);
	}
	return (0);
}
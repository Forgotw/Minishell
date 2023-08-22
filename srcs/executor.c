/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:07:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/22 21:11:02 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* Si on est sur un subshell, dive tout les sub shell j'usq'a cmd */
/* Exec les cmd tant qu'on est pas a next = null, si sur le chemin on rencontre un subshell dive again */
/* Une fois qu'on a exec et que next = null, remonter au upshell, aller sur next et recommencer */

void	print_cmd(t_cmd *ast)
{
	int	i;

	i = 0;
	printf("_______________________\n");
	printf("Cmd type: %i\n", ast->type);
	printf("Link type: %i\n", ast->linktype);
	printf("Redir type: %i\n", ast->redirtype);
	if (ast->cmd)
	{
		printf("Array: ");
		while (ast->cmd[i])
		{
			printf("\"%s\" ", ast->cmd[i]);
			i++;
		}
		printf("\n");
	}
	printf("Heredoc: %i\n", ast->heredoc);
	printf("Infile: %i\n", ast->infile);
	printf("Outfile: %i\n", ast->outfile);
	printf("_______________________\n");
}

t_cmd	*execute_subshell(t_cmd *ast)
{
	while (ast->subshell)
		ast = ast->subshell;
	return (ast);
}

t_cmd	*execute_cmd(t_cmd *ast)
{
	print_cmd(ast);
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
		else if (ast->type == CMD)
			ast = execute_cmd(ast);
	}
	printf("   OOOOO finish executor OOOOO\n");
	return (0);
}
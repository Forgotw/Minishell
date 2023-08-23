/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:07:28 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/23 12:52:39 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* Si on est sur un subshell, dive tout les sub shell j'usq'a cmd */
/* Exec les cmd tant qu'on est pas a next = null, si sur le chemin on rencontre un subshell dive again */
/* Une fois qu'on a exec et que next = null, remonter au upshell, aller sur next et recommencer */

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		printf("--- No array---\n");
	else
	{
		//printf("Array: ");
		while (array[i])
		{
			printf("\"%s\" ", array[i]);
			i++;
		}
		printf("\n");
	}
}

void	print_cmd(t_cmd *ast, char *indent)
{
	int	i;

	i = 0;
	printf("%s_______________________\n", indent);
	printf("%s----%p----\n", indent, ast);
	printf("%sCmd type: %i\n", indent, ast->type);
	printf("%sLink type: %i\n", indent, ast->linktype);
	printf("%sRedir type: %i\n", indent, ast->redirtype);
	printf("%scmd: ", indent);
	print_array(ast->cmd);
	printf("%sHeredoc: %i\n", indent, ast->heredoc);
	printf("%sInfile: %i\n", indent, ast->infile);
	printf("%sOutfile: %i\n", indent, ast->outfile);
	printf("%s_______________________\n", indent);
}

t_cmd	*execute_subshell(t_cmd *ast)
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

t_cmd	*execute_cmd(t_cmd *ast)
{
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
				printf("\n\n\033[36;1m==============Going next=============\033[0m\n\n\n");
				ast = ast->next;
				break ;
			}
		}
	}
	return (ast);
}

int	executor(t_cmd *ast)
{
	printf("\n\n\n\n");
	while (ast)
	{
		//printf("while executor add: %p\n", ast);
		//print_cmd(ast);
		if (ast->type == SUBSHELL)
			ast = execute_subshell(ast);
		else if (ast->type == CMD)
			ast = execute_cmd(ast);
	}
	printf("   OOOOO finish executor OOOOO\n");
	return (0);
}
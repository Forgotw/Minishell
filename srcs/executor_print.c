/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:10 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 17:23:05 by lsohler          ###   ########.fr       */
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
		while (array[i])
		{
			printf("\"%s\" ", array[i]);
			i++;
		}
		printf("\n");
	}
}

void	print_token_exec(t_token *token, int redir)
{
	if (!token)
	{
		printf("--- No token ---\n");
		return ;
	}
	while (token)
	{
		printf("\033[36;1m%s\033[33;1m(%i)\033[35;1m(%i)", token->str, token->type, token->join);
		if (redir)
			printf("\033[31;1m(%i) ", token->redir);
		else
			printf(" ");
		token = token->next;
	}
	printf("\033[0m\n");
}

void	print_cmd(t_cmd *ast, char *indent)
{
	printf("%s_______________________\n", indent);
	printf("%s----%p----\n", indent, ast);
	printf("%s-up-%p----\n", indent, ast->upshell);
	printf("%sCmd type: %i\n", indent, ast->type);
	printf("%sLink type: %i\n", indent, ast->linktype);
	printf("%sRedir type: %i\n", indent, ast->redirtype);
	printf("%scmd: ", indent);
	print_array(ast->cmd);
	printf("%stok cmd: ", indent);
	print_token_exec(ast->tok, 0);
	printf("%stok redir: ", indent);
	print_token_exec(ast->redir, 1);
	printf("%sHeredoc: %i\n", indent, ast->heredoc);
	printf("%sInfile: %i\n", indent, ast->infile);
	printf("%sOutfile: %i\n", indent, ast->outfile);
	printf("%s_______________________\n", indent);
}

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

t_cmd	*execute_cmd_print(t_cmd *ast)
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

int	executor_print(t_cmd *ast)
{
	printf("\n\n\n\n");
	while (ast)
	{
		//printf("while executor add: %p\n", ast);
		//print_cmd(ast);
		if (ast->type == SUBSHELL)
			ast = execute_subshell_print(ast);
		else if (ast->type == CMD || ast->type == 0)
			ast = execute_cmd_print(ast);
	}
	printf("   OOOOO finish executor OOOOO\n");
	return (0);
}
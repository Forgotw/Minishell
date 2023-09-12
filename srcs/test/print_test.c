/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:38:45 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 19:40:21 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("\033[36;1m%s\033[33;1m(%i)\033[35;1m(%i)",
			token->str, token->type, token->join);
		if (redir)
			printf("\033[31;1m(%i) ", token->redir);
		else
			printf(" ");
		token = token->next;
	}
	printf("\n");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:36:51 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/23 12:43:40 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(int cmdtype)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = cmdtype;
	cmd->linktype = 0;
	cmd->redirtype = 0;
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->heredoc = 0;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->subshell = NULL;
	cmd->upshell = NULL;
	cmd->pid = 0;
	// if (cmdtype == SUBSHELL)
	// {
	// 	cmd->cmd = malloc(sizeof (char *) * 3);
	// 	cmd->cmd[0] = ft_strdup("This is a subshell");
	// 	cmd->cmd[1] = NULL;
	// }
	return (cmd);
}

/* Si on est sur une commande next = subshell ast = next */
/* Si on est sur un subshell subshell = new upshell = ast et ast = subshell */
/* Si on est sur NULL, ast = new type = subshell upshell = NULL*/

/* Creer une struct subshell et descend */
t_cmd	*create_subshell(t_token **token, t_cmd *ast)
{
	//printf("THIS IS A SUBSHELL\n");
	if (ast == NULL)
	{
		printf("          CREATING SUBSHELL ON null\n");
		ast = new_cmd(SUBSHELL);
	}
	else if (ast->type == CMD)
	{
		printf("          CREATING SUBSHELL ON next\n");
		ast->next = new_cmd(SUBSHELL);
		ast->next->upshell = ast->upshell;
		ast = ast->next;
	}
	else if (ast->type == SUBSHELL)
	{
		printf("          CREATING SUBSHELL ON subshell\n");
		ast->subshell = new_cmd(SUBSHELL);
		ast->subshell->upshell = ast;
		ast = ast->subshell;
	}
	else if (ast->type == 0)
		ast->type = SUBSHELL;
	printf("          SUBSHELL ADD: %p\n", ast);
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

t_cmd	*assign_redir(t_token **tokens, t_cmd *ast)
{
	t_token *token;

	token = *tokens;
	if (ast == NULL)
		ast = new_cmd(0);
	if (token->type == L_REDIR)
		ast->infile = open(token->next->str, O_RDONLY);
	else if (token->type == R_REDIR)
		ast->outfile = open(token->next->str, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (token->type == D_L_REDIR)
		ast->infile = 128;
	else if (token->type == D_R_REDIR)
		ast->outfile = open(token->next->str, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (ast->infile < 0 || ast->outfile < 0)
	{
		printf("Minishell: %s: No such file or directory\n", token->str);
		exit (-1);
	}
	*tokens = token->next->next;
	return (ast);
}

void	create_cmd_array(t_token **tokens, t_cmd *ast)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (token->type == WORD)
		{
			ast->cmd = array_add_str(ast->cmd, token->str);
			token = token->next;
		}
		else if (token->type == L_REDIR || token->type == R_REDIR
			|| token->type == D_L_REDIR || token->type == D_R_REDIR)
			assign_redir(&token, ast);
		else
			break ;
	}
	printf("          CREATING CMD AT: %p\n", ast);
	printf("          CREATING CMD: upshell add: %p\n", ast->upshell);
	printf("          CREATING CMD: ");
	print_array(ast->cmd);
	*tokens = token;
}

t_cmd	*create_cmd(t_token **tokens, t_cmd *ast)
{
	t_token *token;

	token = *tokens;
	if (ast == NULL)
		ast = new_cmd(CMD);
	else if (ast->type == SUBSHELL)
	{
		printf("   CREATING CMD ON SUBSHELL\n");
		ast->subshell = new_cmd(CMD);
		ast->subshell->upshell = ast;
		ast = ast->subshell;
	}
	else if (ast->type == CMD)
	{
		printf("   CREATING CMD ON NEXT\n");
		ast->next = new_cmd(CMD);
		ast->next->upshell = ast->upshell;
		ast = ast->next;
	}
	else
	{
		printf("   CREATING CMD ON IN PLACE\n");
		ast->type = CMD;
	}
	create_cmd_array(tokens, ast);
	return (ast);
}

t_cmd	*assign_link(t_token **token, t_cmd *ast)
{
	printf("Test in assign_link: ast add: %p\n", ast);
	printf("Test in assign_link type: %i\n", (*token)->type);
	ast->linktype = (*token)->type;
	// printf("Test in assign_link: 2\n");
	ast->next = new_cmd(0);
	// printf("Test in assign_link: 3\n");
	ast->next->upshell = ast->upshell;
	// printf("Test in assign_link: 4\n");
	ast = ast->next;
	// printf("Test in assign_link: 5\n");
	*token = (*token)->next;
	// printf("Test in assign_link: 6\n");
	return (ast);
}

t_cmd	*create_ast(t_token *token)
{
	t_cmd	*ast;
	t_cmd	*head;

	head = NULL;
	ast = NULL;
	while (token)
	{
		//printf("Address: %p\n", ast);
		if (token->type == O_PAR)
		{
			printf("THIS IS A SUBSHELL in create_ast\n");
			ast = create_subshell(&token, ast);
		}
		else if (token->type == C_PAR)
		{
			printf("THIS IS A CLOSE SUBSHELL in create_ast\n");
			ast = close_subshell(&token, ast);
		}
		else if (token->type == WORD)
		{
			printf("THIS IS A CMD in create_ast\n");
			ast = create_cmd(&token, ast);
		}
		else if (token->type == L_REDIR || token->type == R_REDIR
			|| token->type == D_L_REDIR || token->type == D_R_REDIR)
		{
			printf("THIS IS A REDIR in create_ast\n");
			ast = assign_redir(&token, ast);
		}
		else if (token->type == AND || token->type == OR
			|| token->type == PIPE)
		{
			printf("THIS IS A LINK in create_ast\n");
			ast = assign_link(&token, ast);
		}
		if (head == NULL && ast != NULL)
			head = ast;
	}
	return (head);
}

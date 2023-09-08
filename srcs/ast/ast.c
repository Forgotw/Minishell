/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:36:51 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/08 15:38:34 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_redir_token(t_token **token, t_cmd *ast, t_shell *shell)
{
	int		redir_type;
	t_token	*new_redir;

	if (ast == NULL)
		ast = new_cmd(0, shell);
	if (ast->type == SUBSHELL)
	{
		// ast->subshell = new_cmd(0, shell);
		// ast->subshell->upshell = ast;
		// ast = ast->subshell;
		ast = create_node_on_subshell(0, shell, ast);
	}
	redir_type = (*token)->type;
	(*token) = (*token)->next;
	if ((*token)->type <= WORD)
	{
		new_redir = token_dup(*token);
		new_redir->redir = redir_type;
		token_add_back(&ast->redir, new_redir);
		while ((*token) && (*token)->join)
		{
			*token = (*token)->next;
			new_redir = token_dup(*token);
			new_redir->redir = redir_type;
			token_add_back(&ast->redir, new_redir);
		}
	}
	(*token) = (*token)->next;
	return (ast);
}

void	create_cmd_token(t_token **tokens, t_cmd *ast, t_shell *shell)
{
	t_token	*token;
	t_token	*new;

	token = *tokens;
	while (token)
	{
		if (token->type <= WORD)
		{
			//ast->cmd = array_add_str(ast->cmd, token->str);
			new = token_dup(token);
			token_add_back(&ast->tok, new);
			// if (!ast->tok)
			// {
			// 	ast->tok = new_tok(NULL, token->str, token->type);
			// 	tokhead = ast->tok;
			// }
			// else
			// {
			// 	ast->tok->next = new_tok(ast->tok, token->str, token->type);
			// 	ast->tok = ast->tok->next;
			// }
			token = token->next;
		}
		else if (token->type == L_REDIR || token->type == R_REDIR
			|| token->type == D_L_REDIR || token->type == D_R_REDIR)
			create_redir_token(&token, ast, shell);
		else
			break ;
	}
	// printf("          \033[37;1mCREATING CMD AT: %p\n", ast);
	// printf("          \033[37;1mCREATING CMD: upshell add: %p\n", ast->upshell);
	*tokens = token;
}

t_cmd	*create_cmd(t_token **tokens, t_cmd *ast, t_shell *shell)
{
	//t_token *token;

	//token = *tokens;
	if (ast == NULL)
		ast = new_cmd(CMD, shell);
	else if (ast->type == SUBSHELL)
	{
		// printf("   CREATING CMD ON SUBSHELL\n");
		// ast->subshell = new_cmd(CMD, shell);
		// ast->subshell->upshell = ast;
		// ast = ast->subshell;
		ast = create_node_on_subshell(CMD, shell, ast);
	}
	else if (ast->type == CMD)
	{
		// printf("   CREATING CMD ON NEXT\n");
		// ast->next = new_cmd(CMD, shell);
		// ast->next->upshell = ast->upshell;
		// ast = ast->next;
		ast = create_node_on_next(CMD, shell, ast);
	}
	else
	{
		// printf("   CREATING CMD ON IN PLACE\n");
		ast->type = CMD;
	}
	create_cmd_token(tokens, ast, shell);
	return (ast);
}

t_cmd	*assign_link(t_token **token, t_cmd *ast, t_shell *shell)
{
	ast->linktype = (*token)->type;
	ast->next = new_cmd(0, shell);
	ast->next->upshell = ast->upshell;
	ast = ast->next;
	*token = (*token)->next;
	return (ast);
}

t_cmd	*create_ast(t_token *token, t_shell *shell)
{
	t_cmd	*ast;
	t_cmd	*head;

	head = NULL;
	ast = NULL;
	while (token)
	{
		if (token->type == O_PAR)
			ast = create_subshell(&token, ast, shell);
		else if (token->type == C_PAR)
			ast = close_subshell(&token, ast);
		else if (token->type <= WORD)
			ast = create_cmd(&token, ast, shell);
		else if (token->type == L_REDIR || token->type == R_REDIR
			|| token->type == D_L_REDIR || token->type == D_R_REDIR)
			ast = create_redir_token(&token, ast, shell);
		else if (token->type == AND || token->type == OR
			|| token->type == PIPE)
			ast = assign_link(&token, ast, shell);
		if (head == NULL && ast != NULL)
			head = ast;
	}
	return (head);
}

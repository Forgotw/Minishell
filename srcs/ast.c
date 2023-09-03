/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:36:51 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 18:00:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(int cmdtype, t_shell *shell)
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
	cmd->tok = NULL;
	cmd->redir = NULL;
	cmd->shell = shell;
	return (cmd);
}

/**/
t_cmd	*create_redir_token(t_token **token, t_cmd *ast, t_shell *shell)
{
	int		redir_type;
	t_token	*new_redir;

	if (ast == NULL)
		ast = new_cmd(0, shell);
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
		ast->subshell = new_cmd(CMD, shell);
		ast->subshell->upshell = ast;
		ast = ast->subshell;
	}
	else if (ast->type == CMD)
	{
		// printf("   CREATING CMD ON NEXT\n");
		ast->next = new_cmd(CMD, shell);
		ast->next->upshell = ast->upshell;
		ast = ast->next;
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
	// printf("Test in assign_link: ast add: %p\n", ast);
	// printf("Test in assign_link type: %i\n", (*token)->type);
	ast->linktype = (*token)->type;
	// printf("Test in assign_link: 2\n");
	ast->next = new_cmd(0, shell);
	// printf("Test in assign_link: 3\n");
	ast->next->upshell = ast->upshell;
	// printf("Test in assign_link: 4\n");
	ast = ast->next;
	// printf("Test in assign_link: 5\n");
	*token = (*token)->next;
	// printf("Test in assign_link: 6\n");
	return (ast);
}

t_cmd	*create_ast(t_token *token, char **envp)
{
	t_cmd	*ast;
	t_cmd	*head;
	t_shell	*shell;

	head = NULL;
	ast = NULL;
	shell = init_shell_data(envp);
	while (token)
	{
		//printf("Address: %p\n", ast);
		if (token->type == O_PAR)
		{
			// printf("THIS IS A SUBSHELL in create_ast\n");
			ast = create_subshell(&token, ast, shell);
		}
		else if (token->type == C_PAR)
		{
			// printf("THIS IS A CLOSE SUBSHELL in create_ast\n");
			ast = close_subshell(&token, ast);
		}
		else if (token->type <= WORD)
		{
			// printf("THIS IS A CMD in create_ast\n");
			ast = create_cmd(&token, ast, shell);
		}
		else if (token->type == L_REDIR || token->type == R_REDIR
			|| token->type == D_L_REDIR || token->type == D_R_REDIR)
		{
			// printf("THIS IS A REDIR in create_ast\n");
			ast = create_redir_token(&token, ast, shell);
		}
		else if (token->type == AND || token->type == OR
			|| token->type == PIPE)
		{
			// printf("THIS IS A LINK in create_ast\n");
			ast = assign_link(&token, ast, shell);
		}
		if (head == NULL && ast != NULL)
			head = ast;
	}
	return (head);
}

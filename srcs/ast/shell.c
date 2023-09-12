/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:17:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 19:35:46 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(int cmdtype, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	ast_address_collector(&shell->collector, (void *)cmd, cmdtype);
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

t_cmd	*create_node_on_subshell(int type, t_shell *shell, t_cmd *ast)
{
	ast->subshell = new_cmd(type, shell);
	ast->subshell->upshell = ast;
	ast = ast->subshell;
	return (ast);
}

t_cmd	*create_node_on_next(int type, t_shell *shell, t_cmd *ast)
{
	ast->next = new_cmd(type, shell);
	ast->next->upshell = ast->upshell;
	ast = ast->next;
	return (ast);
}

t_shell	*init_shell_data(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->env = ft_arrdup(envp);
	shell->status = TRUE;
	shell->prev_pipe_in = -1;
	shell->collector = NULL;
	return (shell);
}

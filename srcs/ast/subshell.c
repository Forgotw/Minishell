/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:22:02 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 20:05:43 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Si on est sur une commande next = subshell ast = next */
/* Si on est sur un subshell subshell = new upshell = ast et ast = subshell */
/* Si on est sur NULL, ast = new type = subshell upshell = NULL*/
/* Creer une struct subshell et descend */
t_cmd	*create_subshell(t_token **token, t_cmd *ast, t_shell *shell)
{
	if (ast == NULL)
		ast = new_cmd(SUBSHELL, shell);
	else if (ast->type == CMD)
		ast = create_node_on_next(SUBSHELL, shell, ast);
	else if (ast->type == SUBSHELL)
		ast = create_node_on_subshell(SUBSHELL, shell, ast);
	else if (ast->type == 0)
		ast->type = SUBSHELL;
	*token = (*token)->next;
	return (ast);
}

t_cmd	*close_subshell(t_token **token, t_cmd *ast)
{
	ast = ast->upshell;
	*token = (*token)->next;
	return (ast);
}

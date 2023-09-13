/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:04:51 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/13 15:44:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *ast)
{
	if (!ast)
		return ;
	if (ast->cmd)
		free_array(ast->cmd);
	if (ast->path != NULL)
		free(ast->path);
	if (ast->tok != NULL)
		free_token(ast->tok);
	if (ast->redir != NULL)
		free_token(ast->redir);
	free(ast);
}

t_address	*new_collector_node(void *address, int type)
{
	t_address	*new;

	new = malloc(sizeof(t_address));
	new->address = address;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ast_address_collector(t_address **collector, void *address, int type)
{
	t_address	*tmp;

	if (*collector == NULL)
		*collector = new_collector_node(address, type);
	else
	{
		tmp = *collector;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_collector_node(address, type);
	}
}

void	free_ast(t_shell *shell)
{
	t_address	*tmp;

	tmp = shell->collector;
	while (shell->collector)
	{
		tmp = shell->collector->next;
		free_cmd((t_cmd *)shell->collector->address);
		free(shell->collector);
		shell->collector = tmp;
	}
	shell->collector = NULL;
	close_all_fd(shell->fdlist);
	shell->fdlist = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:13:36 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 19:56:25 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_g_status(int *status)
{
	if (*status == 127)
		g_status = *status;
	else if (WIFEXITED(g_status))
	{
		g_status = WEXITSTATUS(g_status);
	}
	else if (WIFSIGNALED(g_status))
	{
		g_status = WTERMSIG(g_status) + 128;
	}
	else
		g_status = *status;
}

void	boolean_link(t_cmd *node)
{
	if (node->linktype == AND && !g_status)
		node->shell->status = TRUE;
	else if (node->linktype == AND && g_status)
		node->shell->status = FALSE;
	else if (node->linktype == OR && g_status)
		node->shell->status = TRUE;
	else if (node->linktype == OR && !g_status)
		node->shell->status = FALSE;
}

t_cmd	*skip_subshell(t_cmd *node)
{
	boolean_link(node);
	if (node->next)
		node = node->next;
	else if (node->upshell)
		exit (0);
	return (node);
}

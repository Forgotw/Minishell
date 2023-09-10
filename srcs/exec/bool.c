/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:13:36 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/10 19:44:56 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_ret_status(int *status)
{
	// fprintf(stdout, "ret_status in get_ret_status: %i\n", ret_status);
	// fprintf(stdout, "status in get_ret_status: %i\n", *status);
	if (*status == 127)
		ret_status = *status;
	else if (WIFEXITED(ret_status))
	{
		ret_status = WEXITSTATUS(ret_status);
	}
	else if (WIFSIGNALED(ret_status))
	{
		ret_status = WTERMSIG(ret_status) + 128;
	}
	else
		ret_status = *status;
}

void	boolean_link(t_cmd *node)
{
	if (node->linktype == AND && !ret_status)
		node->shell->status = TRUE;
	else if (node->linktype == AND && ret_status)
		node->shell->status = FALSE;
	else if (node->linktype == OR && ret_status)
		node->shell->status = TRUE;
	else if (node->linktype == OR && !ret_status)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nav.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:57:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 19:56:36 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*nav_subshell(t_cmd *node, int *status)
{
	if (node->shell->status == FALSE)
		node = skip_subshell(node);
	if (node->subshell && node->shell->status == TRUE)
	{
		node->pid = fork();
		if (node->pid == 0)
		{
			node = node->subshell;
		}
		else
		{
			waitpid(node->pid, &g_status, 0);
			get_g_status(status);
			if (node->next)
				node = node->next;
			else if (node->upshell)
				exit (0);
			else
				return (NULL);
		}
	}
	return (node);
}

t_cmd	*nav_cmd(t_cmd *node, int *status)
{
	if (node->shell->status == TRUE)
	{
		execute_cmd(node, status);
		get_g_status(status);
	}
	boolean_link(node);
	if (node->next)
		node = node->next;
	else
	{
		if (node->upshell)
		{
			exit (0);
		}
		else
		{
			return (NULL);
		}
	}
	return (node);
}

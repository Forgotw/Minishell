/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 21:12:40 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_execve(t_cmd *node)
{
	if (is_builtin(cmd[0]))
		return (exec_builtin(node->cmd, node->shell));
	else
		return (execve(node->path, node->cmd, node->shell->env));
	return (-1);
}
/* Redir pipe */
/* Redir file from subshell */
/* Redir file */
/* Expand and join */
/* fork */

int	execute_cmd(t_cmd *node, int *status)
{
	if (redir(node, status))
		return (*status);
	if (expand_and_join(node, status))
		return (*status);
	node->pid = fork();
	
}

t_cmd	*nav_subshell(t_cmd *node, int *status)
{
	while (node->subshell)
	{
		node = node->subshell;
	}
	return (node);
}

t_cmd	*nav_cmd(t_cmd *node, int *status)
{
	execute_cmd(node, status);
	if (node->next)
		node = node->next;
	else
	{
		while (ast)
		{
			node = node->upshell;
			if (node && node->next)
			{
				node = node->next;
				break ;
			}
		}
	}
	return (node);
}

int	executor(t_cmd *node)
{
	int	status;

	status = 0;
	while (node)
	{
		if (node->type == SUBSHELL)
			node = nav_subshell(node, &status);
		else if (node->type == CMD || node->type == 0)
			node = nav_cmd(node, &status);
	}
	return (0);
}
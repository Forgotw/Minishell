/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/30 16:22:54 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	my_execve(t_cmd *node, int *status)
{
	if (is_builtin(node->cmd[0]))
		return (exec_builtin(node->cmd, node->shell));
	else
	{
		node->pid = fork();
		if (node->pid == 0)
			return (execve(node->path, node->cmd, node->shell->env));
		else
			perror("Minishell fork error");
	}
	return (-1);
}
/* Redir pipe */
/* Redir file from subshell */
/* Redir file */
/* Expand join et creer cmd array*/
/* fork sauf si builtin */

int	execute_cmd(t_cmd *node, int *status)
{
	if (redir(node, status))
		return (*status);
	if (expand_and_join(node, status))
		return (*status);
	status = my_execve(node, status);
}

t_cmd	*nav_subshell(t_cmd *node, int *status)
{
	if (node->subshell)
	// while (node->subshell)
	// {
	// 	node->pid = fork();
	// 	if (node->pid < 0)
	// 		perror("Minishell fork error");
	// 	node = node->subshell;
	// }
	// return (node);
}

t_cmd	*nav_cmd(t_cmd *node, int *status)
{
	execute_cmd(node, status);
	if (node->next)
		node = node->next;
	else
	{
		while (node)
		{
			node = node->upshell;
			if (node && node->next)
			{
				if (node->pid == 0)
					kill(node->pid, SIGTERM);
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
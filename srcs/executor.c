/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 17:56:39 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_execve(t_cmd *node, int *status)
{
	(void)status;

	if (is_builtin(node->cmd[0]))
		return (exec_builtin(node->cmd, node->shell));
	else
	{
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
	if (node->tok)
	{
		node->tok = expand_token(node->tok, node->shell);
		node->cmd = create_cmd_array(node->tok);
	}
	if (node->redir)
	{
		node->redir = expand_token(node->redir, node->shell);
		node->redir = join_redir_token(node->redir);
	}
	node->shell->status = assign_redir(node->redir, node);
	if (!node->shell->status)
	{
		fork_and_pipe(node, status);
		node->shell->status = my_execve(node, status);
		if (node->pid > 0 && node->linktype == PIPE)
		{
			if (node->shell->prev_pipe_in != 0)
				close(node->shell->prev_pipe_in);
			if (node->linktype == PIPE)
			{
				node->shell->prev_pipe_in = node->shell->pipefd[0];
				close(node->shell->pipefd[1]);
			}
			else
				node->shell->prev_pipe_in = STDIN;
		}
	}
	return (0);
}

t_cmd	*nav_subshell(t_cmd *node, int *status)
{
	(void)status;

	if (node->subshell)
	{
		// node->pid = fork();
		// if (node->pid == 0)
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
		while (node)
		{
			// if (node->pid == 0)
			// 	kill(node->pid, SIGTERM);
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
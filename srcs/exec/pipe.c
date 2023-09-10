/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:00:27 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/10 11:39:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_pipe(t_cmd *node)
{
	if (node->linktype == PIPE)
		if (pipe(node->shell->pipefd) == -1)
			perror("pipe error");
	if (node->linktype == PIPE
		|| !is_builtin(node->cmd[0]))
	{
		node->pid = fork();
		if (node->pid < 0)
			perror("fork");
	}
}

void	redir_child(t_cmd *node)
{
	if (node->infile)
		dup2(node->infile, STDIN_FILENO);
	else if (node->shell->prev_pipe_in != -1)
		dup2(node->shell->prev_pipe_in, STDIN_FILENO);
	if (node->outfile)
		dup2(node->outfile, STDOUT_FILENO);
	else if (node->linktype == PIPE)
		dup2(node->shell->pipefd[1], STDOUT_FILENO);
	else
		dup2(STDOUT_FILENO, STDOUT_FILENO);
}

void	redir_prev_pipe_in(t_cmd *node)
{
	if (node->shell->prev_pipe_in != -1)
	{
		close(node->shell->prev_pipe_in);
	}
	if (node->linktype == PIPE)
	{
		node->shell->prev_pipe_in = node->shell->pipefd[0];
		close(node->shell->pipefd[1]);
	}
	else
		node->shell->prev_pipe_in = -1;
}

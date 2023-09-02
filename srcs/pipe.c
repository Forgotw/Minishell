/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:00:27 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/02 17:52:02 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fork_and_pipe(t_cmd *node, int *status)
{
	(void)status;

	if (node->linktype == PIPE)
	{
		if (pipe(node->shell->pipefd) < 0)
			perror("pipe");
		node->pid = fork();
		if (node->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		dup2(node->shell->prev_pipe_in, STDIN);
		if (node->infile)
			dup2(node->infile, STDIN);
		dup2(node->shell->pipefd[1], STDOUT);
		close(node->shell->pipefd[0]);
		if (node->outfile)
			dup2(node->outfile, STDOUT);
	}
}
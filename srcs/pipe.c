/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:00:27 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 12:40:13 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_pipe(t_cmd *node, int *status)
{
	(void)status;
	if (node->linktype == PIPE)
		if (pipe(node->shell->pipefd) == -1)
			perror("pipe error");
	// if ((!ft_strcmp("echo", node->cmd[0]) && node->linktype == PIPE)
	// 	|| (!ft_strcmp("export", node->cmd[0]) && node->linktype == PIPE)
	// 	|| (!ft_strcmp("pwd", node->cmd[0]) && node->linktype == PIPE)
	// 	|| !is_builtin(node->cmd[0]))
	if (node->linktype == PIPE || !is_builtin(node->cmd[0]))
	{
		node->pid = fork();
		if (node->pid < 0)
			perror("fork");
	}
}

void	redir_child(t_cmd *node, int *status)
{
	(void)status;
	if (node->infile)
		dup2(node->infile, STDIN_FILENO);
	else if (node->shell->prev_pipe_in != -1)
		dup2(node->shell->prev_pipe_in, STDIN_FILENO);
	if (node->outfile)
		dup2(node->outfile, STDOUT_FILENO);
	else if (node->linktype == PIPE)
	{
		dup2(node->shell->pipefd[1], STDOUT_FILENO);
		// close(node->shell->pipefd[0]);
	}
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

// void	redir_child(t_list *cur, t_files *files, int *pipefd, int prev_pipe_in)
// {
// 	if (!cur->path)
// 		cmd_error(&cur, cur->cmd[0]);
// 	if (cur->prev == NULL)
// 		dup2(files->infile, STDIN_FILENO);
// 	else
// 	{
// 		dup2(prev_pipe_in, STDIN_FILENO);
// 		close(prev_pipe_in);
// 	}
// 	if (cur->next)
// 	{
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[0]);
// 	}
// 	else
// 		dup2(files->outfile, STDOUT_FILENO);
// }

// void	redir_prev_pipe_in(t_list *tmp, int *pipefd, int *prev_pipe_in)
// {
// 	if (*prev_pipe_in != -1)
// 		close(*prev_pipe_in);
// 	if (tmp->next)
// 	{
// 		*prev_pipe_in = pipefd[0];
// 		close(pipefd[1]);
// 	}
// }

// void	fork_and_pipe(t_list **tmp, int *pipefd)
// {
// 	if ((*tmp)->next)
// 		if (pipe(pipefd) < 0)
// 			perror_and_exit("pipe");
// 	(*tmp)->pid = fork();
// 	if ((*tmp)->pid < 0)
// 		perror_and_exit("fork");
// }

// void	execute_commands(t_list **child, t_files *files, char **envp)
// {
// 	int		pipefd[2];
// 	int		status;
// 	int		prev_pipe_in;
// 	pid_t	wpid;
// 	t_list	*tmp;

// 	tmp = *child;
// 	prev_pipe_in = -1;
// 	while (tmp)
// 	{
// 		//parent
// 		fork_and_pipe(&tmp, pipefd);
// 		i(f (tmp->pid == 0))
// 		{
// 			redir_child(tmp, files, pipefd, prev_pipe_in);
// 			if (execve(tmp->path, tmp->cmd, envp) < 0)
// 				perror_and_exit("execve");
// 		}
// 		else
// 			redir_prev_pipe_in(tmp, pipefd, &prev_pipe_in);
// 		tmp = tmp->next;
// 	}
// 	if (prev_pipe_in != -1)
// 		close(prev_pipe_in);
// 	while (wpid > 0)
// 		wpid = wait(&status);
// }
	// if (1)
	// {
	// 	if (pipe(node->shell->pipefd) < 0)
	// 		perror("pipe");
	// 	node->pid = fork();
	// 	if (node->pid == -1)
	// 	{
	// 		perror("fork");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	if (node->linktype == PIPE)
	// 	{
	// 		dup2(node->shell->prev_pipe_in, STDIN);
	// 		if (node->infile)
	// 			dup2(node->infile, STDIN);
	// 		dup2(node->shell->pipefd[1], STDOUT);
	// 		close(node->shell->pipefd[0]);
	// 		if (node->outfile)
	// 			dup2(node->outfile, STDOUT);
	// 	}
	// }
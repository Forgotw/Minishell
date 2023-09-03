/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/03 19:38:24 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_execve(t_cmd *node, int *status)
{
	(void)status;

	if (is_builtin(node->cmd[0]))
		return (exec_builtin(node->cmd, node->shell, node));
	else
	{
		if (node->pid == 0)
		{
			return (execve(node->path, node->cmd, node->shell->env));
		}
		// else
		// 	perror("Minishell fork error");
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
	if (!is_builtin(node->cmd[0]))
		node->shell->status = get_path_type(node->cmd, node);
	if (node->shell->status)
		return (node->shell->status);
	//printf("THE PATH IS: %s\n", node->path);
	node->shell->status = assign_redir(node->redir, node);
	if (node->shell->status)
		return (node->shell->status);
	if (!node->shell->status)
	{
		fork_and_pipe(node, status);
		if (node->pid == 0)
		{
			// exit (fprintf(stderr, "EXITING CHILD PROCESS\n"));
			//fprintf(stderr, "BEFORE FILES DESCRIPTOR: cmd:%s [0]%i [1]%i\n", node->cmd[0], node->shell->pipefd[0], node->shell->pipefd[1]);
			redir_child(node, status);
			//fprintf(stderr, "FILES DESCRIPTOR: cmd:%s [0]%i [1]%i\n", node->cmd[0], node->shell->pipefd[0], node->shell->pipefd[1]);
			node->shell->status = my_execve(node, status);
			if (node->shell->status < 0)
				perror("execve error");
		}
		else
		{
			redir_prev_pipe_in(node);
		}
		waitpid(node->pid, NULL, *status);
	}
	return (0);
}

t_cmd	*nav_subshell(t_cmd *node, int *status)
{
	(void)status;

	if (node->subshell)
	{
		node->pid = fork();
		if (node->pid == 0)
			node = node->subshell;
		else
			waitpid(node->pid, NULL, *status);
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
		if (node->upshell)
		{
			exit (0);
			if (node->next)
				node = node->next;
		}
		else
			return (NULL);
		// while (node)
		// {
		// 	// if (node->pid == 0)
		// 	// 	kill(node->pid, SIGTERM);
		// 	node = node->upshell;
		// 	if (node && node->next)
		// 	{
		// 		node = node->next;
		// 		break ;
		// 	}
		// }
	}
	return (node);
}

int	executor(t_cmd *node)
{
	int	status;

	status = 0;
	if (node)
	{
		if (node->type == SUBSHELL)
			node = nav_subshell(node, &status);
		else if (node->type == CMD || node->type == 0)
			node = nav_cmd(node, &status);
		executor(node);
	}
	return (0);
}
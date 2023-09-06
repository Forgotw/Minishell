/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 14:37:56 by lsohler          ###   ########.fr       */
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
	if (!is_builtin(node->cmd[0]))
		*status = get_path_type(node->cmd, node);
	if (*status)
		return (*status);
	//printf("THE PATH IS: %s\n", node->path);
	*status = assign_redir(node->redir, node);
	if (*status)
		return (*status);
	if (!*status)
	{
		fork_and_pipe(node, status);
		if (node->pid == 0)
		{
			// exit (fprintf(stderr, "EXITING CHILD PROCESS\n"));
			//fprintf(stderr, "BEFORE FILES DESCRIPTOR: cmd:%s [0]%i [1]%i\n", node->cmd[0], node->shell->pipefd[0], node->shell->pipefd[1]);
			redir_child(node, status);
			//fprintf(stderr, "FILES DESCRIPTOR: cmd:%s [0]%i [1]%i\n", node->cmd[0], node->shell->pipefd[0], node->shell->pipefd[1]);
			*status = my_execve(node, status);
			if (status < 0)
				perror("execve error");
		}
		else
		{
			redir_prev_pipe_in(node);
		}
		//if (node->linktype == AND || node->linktype == OR || node->linktype == PIPE)
		waitpid(node->pid, status, 0);
	}
	return (0);
}

t_cmd	*nav_subshell(t_cmd *node, int *status)
{
	if (node->subshell)
	{
		fprintf(stdout, "BEFORE FORKING SUBSHELL\n");
		node->pid = fork();
		if (node->pid == 0)
		{
			fprintf(stdout, "IN NAV CMD CHILD, Before node = node->subshell: node->pid: %i\n", node->pid);
			node = node->subshell;
		}
		else
		{
			fprintf(stdout, "IN NAV CMD PARENT Before waitpid: node->pid: %i\n", node->pid);
			waitpid(node->pid, status, 0);
			fprintf(stdout, "IN NAV CMD PARENT , After waitpid: node->pid: %i\n", node->pid);
			if (node->next)
				node = node->next;
			else if (node->upshell)
				exit (*status);
			else
				return (NULL);
		}
	}
	return (node);
}

t_cmd	*nav_cmd(t_cmd *node, int *status)
{
	//if (node->linktype == AND || node->linktype == OR && WIFEXITED(node->shell->status))
	execute_cmd(node, status);
	fprintf(stdout, "\033[35;1mstatus: %i\033[0m\n", *status);
	if (WIFEXITED(*status))
		ret_status = WEXITSTATUS(*status);
	fprintf(stdout, "\033[35;1mWEXITSTATUS(status): %i\033[0m\n", ret_status);
	fprintf(stdout, "\033[35;1mnode->shell->status: %i\033[0m\n", node->shell->status);
	if (node->next)
		node = node->next;
	else
	{
		if (node->upshell)
		{
			fprintf(stdout, "IN NAV CMD, Before exit: node->upshell->pid: %i\n", node->upshell->pid);
			exit (0);
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
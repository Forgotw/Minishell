/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/08 18:41:44 by lsohler          ###   ########.fr       */
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
			fprintf(stderr, "FILES DESCRIPTOR: cmd:%s [0]%i [1]%i\n", node->cmd[0], node->shell->pipefd[0], node->shell->pipefd[1]);
			*status = my_execve(node, status);
			if (status < 0)
				perror("execve error");
		}
		else
		{
			waitpid(node->pid, status, 0);
			fprintf(stdout, "BEFORE REDIR PREV PIPE IN IN execute_cmd\n");
			redir_prev_pipe_in(node);
		}
		//if (node->linktype == AND || node->linktype == OR || node->linktype == PIPE)
	}
	return (0);
}

t_cmd	*nav_subshell(t_cmd *node, int *status)
{
	if (node->shell->status == FALSE)
	{
		boolean_link(node, status);
		if (node->next)
			node = node->next;
		else if (node->upshell)
			exit (0);
	}
	if (node->subshell && node->shell->status == TRUE)
	{
		// fprintf(stdout, "BEFORE FORKING SUBSHELL\n");
		node->pid = fork();
		if (node->pid == 0)
		{
			// fprintf(stdout, "IN NAV CMD CHILD, Before node = node->subshell: node->pid: %i\n", node->pid);
			node = node->subshell;
		}
		else
		{
			// fprintf(stdout, "IN NAV CMD PARENT Before waitpid: node->pid: %i\n", node->pid);
			waitpid(node->pid, status, 0);
			// fprintf(stdout, "IN NAV CMD PARENT , After waitpid: node->pid: %i\n", node->pid);
			if (node->next)
				node = node->next;
			else if (node->upshell)
				exit (0);
			else
				return (NULL);
		}
	}
	return (node);
	// if (node->subshell)
	// {
	// 	fprintf(stdout, "BEFORE CHEKING STATUS FOR FORK\n");
	// 	if (node->shell->status == TRUE)
	// 	{
	// 		fprintf(stdout, "BEFORE FORKING SUBSHELL\n");
	// 		node->pid = fork();
	// 	}
	// 	if (node->shell->status == TRUE && node->pid == 0)
	// 	{
	// 		// fprintf(stdout, "IN NAV CMD CHILD, Before node = node->subshell: node->pid: %i\n", node->pid);
	// 		fprintf(stdout, "BEFORE GOING SUBSHELL\n");
	// 		node = node->subshell;
	// 	}
	// 	else
	// 	{
	// 		// fprintf(stdout, "IN NAV CMD PARENT Before waitpid: node->pid: %i\n", node->pid);
	// 		if (node->shell->status == TRUE)
	// 		{
	// 			fprintf(stdout, "AFTER CHECKING STATUS FOR WAITPID\n");
	// 			waitpid(node->pid, status, 0);
	// 		}
	// 		// fprintf(stdout, "IN NAV CMD PARENT , After waitpid: node->pid: %i\n", node->pid);
	// 		if (node->next)
	// 		{
	// 			fprintf(stdout, "GOING ON NEXT NODE\n");
	// 			node = node->next;
	// 		}
	// 		else if (node->upshell)
	// 		{
	// 			if (node->shell->status == TRUE)
	// 				exit (0);
	// 			else
	// 				node = node->upshell;
	// 		}
	// 		else
	// 			return (NULL);
	// 	}
	// }
	// fprintf(stdout, "LAST RETURN NODE\n");
	// return (node);
}

t_cmd	*nav_cmd(t_cmd *node, int *status)
{
	if (node->shell->status == TRUE)
	{
		execute_cmd(node, status);
		get_ret_status(status);
	}
	boolean_link(node, status);
	// if (node->shell->status == TRUE)
	// 	execute_cmd(node, status);
	// fprintf(stdout, "\033[35;1mstatus: %i\033[0m\n", *status);
	// if (WIFEXITED(*status))
	// {
	// 	ret_status = WEXITSTATUS(*status);
	// 	fprintf(stdout, "\033[35;1mWEXITSTATUS(status): %i\033[0m\n", ret_status);
	// }
	// fprintf(stdout, "\033[35;1mnode->shell->status: %i\033[0m\n", node->shell->status);
	// if (node->linktype == AND)
	// {
	// 	fprintf(stdout, "\033[36;1mAND TYPE\033[0m\n");
	// 	if ((WIFEXITED(*status) && WEXITSTATUS(*status)) || *status)
	// 		node->shell->status = FALSE;
	// 	else
	// 		node->shell->status = TRUE;
	// }
	// else if (node->linktype == OR)
	// {
	// 	fprintf(stdout, "\033[36;1mOR TYPE\033[0m\n");
	// 	if ((WIFEXITED(*status) && !WEXITSTATUS(*status)) || !*status)
	// 		node->shell->status = FALSE;
	// 	else
	// 		node->shell->status = TRUE;
	// }
	// if (node->shell->status == 1)
	// 	fprintf(stdout, "\033[32;1m TRUE \033[0m\n");
	// if (node->shell->status == 0)
	// 	fprintf(stdout, "\033[31;1m FALSE \033[0m\n");
	if (node->next)
		node = node->next;
	else
	{
		if (node->upshell)
		{
			if (node->upshell->linktype == PIPE)
			{
				fprintf(stdout, "REDIR PREV PIPE IN AFTER LAST CMD\n");
				redir_prev_pipe_in(node);
			}
			fprintf(stdout, "BEFORE EXIT IN NAV CMD\n");
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/12 18:44:00 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_execve(t_cmd *node)
{
	if (is_builtin(node->cmd[0]))
		return (ret_status = exec_builtin(node->cmd, node->shell, node));
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
	if (node->cmd && !is_builtin(node->cmd[0]))
		*status = get_path_type(node->cmd, node);
	if (*status)
		return (*status);
	*status = assign_redir(node->redir, node);
	if (*status)
		return (*status);
	if (!*status && node->cmd)
	{
		fork_and_pipe(node);
		if (node->pid == 0)
		{
			redir_child(node);
			*status = my_execve(node);
			if (*status < 0)
				perror("execve error");
		}
		else
			redir_prev_pipe_in(node);
		if (node->linktype == AND || node->linktype == OR || !node->linktype)
			waitpid(node->pid, &ret_status, 0);
		else if (node->linktype == PIPE)
			waitpid(node->pid, &ret_status, WNOHANG);
	}
	return (0);
}

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
			waitpid(node->pid, &ret_status, 0);
			get_ret_status(status);
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
		get_ret_status(status);
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

int	executor(t_cmd *node)
{
	int		status;
	int		tmp;
	pid_t	wpid;

	signal_setup(1);
	status = 0;
	while (node)
	{
		if (node->type == SUBSHELL)
			node = nav_subshell(node, &status);
		else if (node->type == CMD || node->type == 0)
			node = nav_cmd(node, &status);
	}
	wpid = wait(&tmp);
	while (wpid > 0)
		wpid = wait(&tmp);
	signal_setup(0);
	unlink(".heredoc");
	return (0);
}

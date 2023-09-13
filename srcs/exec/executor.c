/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/13 15:42:13 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_execve(t_cmd *node)
{
	if (is_builtin(node->cmd[0]))
		return (g_status = exec_builtin(node->cmd, node->shell, node));
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

int	pre_execute_cmd(t_cmd *node, int *status)
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
	return (*status);
}

int	execute_cmd(t_cmd *node, int *status)
{
	*status = pre_execute_cmd(node, status);
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
			waitpid(node->pid, &g_status, 0);
		else if (node->linktype == PIPE)
			waitpid(node->pid, &g_status, WNOHANG);
	}
	return (0);
}

void	recursive_executor(t_cmd *node)
{
	int		status;

	status = 0;
	if (node)
	{
		if (node->type == SUBSHELL)
			node = nav_subshell(node, &status);
		else if (node->type == CMD || node->type == 0)
			node = nav_cmd(node, &status);
		executor(node);
	}
}

int	executor(t_cmd *node)
{
	int		tmp;
	pid_t	wpid;

	signal_setup(1);
	recursive_executor(node);
	wpid = wait(&tmp);
	while (wpid > 0)
		wpid = wait(&tmp);
	signal_setup(0);
	unlink(".heredoc");
	return (0);
}

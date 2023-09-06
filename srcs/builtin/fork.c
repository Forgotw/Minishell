/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:40 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 12:25:46 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_echo(char **cmd, t_cmd *node, t_shell *shell)
{
	if (node->linktype == PIPE)
	{
		if (node->pid == 0)
			exit (node->shell->status = my_echo(cmd, shell));
	}
	else
		shell->status = my_echo(cmd, shell);
	return (0);
}

int	fork_export(char **cmd, t_cmd *node, t_shell *shell)
{
	if (node->linktype == PIPE)
	{
		if (node->pid == 0)
			exit (node->shell->status = export(cmd, shell));
	}
	else
		shell->status = export(cmd, shell);
	return (0);
}

int	fork_pwd(char **cmd, t_cmd *node, t_shell *shell)
{
	if (node->linktype == PIPE)
	{
		if (node->pid == 0)
			exit (node->shell->status = print_working_directory(cmd, shell));
	}
	else
		shell->status = print_working_directory(cmd, shell);
	return (0);
}

int	fork_builtin(char **cmd, t_cmd *node, t_shell *shell,
		int (*function)(char **, t_shell *))
{
	if (node->linktype == PIPE)
	{
		if (node->pid == 0)
			exit (node->shell->status = function(cmd, shell));
	}
	else
		shell->status = function(cmd, shell);
	return (0);
}


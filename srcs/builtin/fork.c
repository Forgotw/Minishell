/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:40 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/08 17:11:28 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_builtin(char **cmd, t_cmd *node, t_shell *shell,
		int (*function)(char **, t_shell *))
{
	if (node->linktype == PIPE
		|| (node->upshell && node->upshell->linktype == PIPE))
	{
		if (node->pid == 0)
			exit (node->shell->status = function(cmd, shell));
	}
	else
		shell->status = function(cmd, shell);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:40 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/10 12:26:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_builtin(char **cmd, t_cmd *node, t_shell *shell,
		int (*function)(char **, t_shell *))
{
	if (node->linktype == PIPE)
	{
		if (node->pid == 0)
			exit (function(cmd, shell));
	}
	else
		return (function(cmd, shell));
	return (0);
}

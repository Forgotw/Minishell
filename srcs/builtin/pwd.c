/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:31:43 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 11:54:54 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_working_directory(char **cmd, t_shell *shell)
{
	char	cwd[1024];

	(void)cmd;
	(void)shell;
	if (getcwd(cwd, 1024) != NULL)
		ft_putendl_fd(cwd, STDOUT);
	else
	{
		perror("Minishell pwd:");
		return (-1);
	}
	return (0);
}

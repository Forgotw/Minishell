/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:31:43 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 13:17:17 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_working_directory(char **cmd, t_shell *shell)
{
	(void)cmd;

	ft_putendl_fd(shell->path, STDOUT);
	return (0);
}

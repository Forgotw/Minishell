/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:29:14 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 17:24:44 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_echo(char **cmd, t_shell *shell)
{
	int	i;
	int	option;

	(void)shell;
	i = 1;
	option = 0;
	if (cmd[1] || cmd[1][0] != '\0')
	{
		if (!ft_strcmp(cmd[1], "-n"))
		{
			option = 1;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], STDOUT);
			ft_putchar_fd(' ', STDOUT);
			i++;
		}
	}
	if (!option)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}
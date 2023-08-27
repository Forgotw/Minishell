/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:32:58 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/27 12:07:20 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putchar_fd("declare -x ", STDOUT);
		ft_putendl_fd(env[i], STDOUT);
	}
}

int	export(char **cmd, char **env)
{
	if (!cmd)
		return (-1);
	else if (!cmd[1])
		print_env(env);
	else
		export_var(&cmd[i]);
	return (0);
}
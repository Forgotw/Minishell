/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:32:04 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/27 17:45:50 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmd_error(void)
{
	ft_putendl_fd(CMD_ENV_ERROR, STDERR);
	return (1);
}

int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], STDOUT);
		i++;
	}
	return (0);
}

int	env(char **cmd, t_shell *shell)
{
	if (cmd[1])
		return (env_cmd_error());
	else
		return (print_env(shell->env));
}

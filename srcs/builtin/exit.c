/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:33:32 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 12:37:04 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg_isdigit(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exit_check_arg(char **cmd, int *ret)
{
	if (ft_arrlen(cmd) > 1)
	{
		if (check_arg_isdigit(cmd[1]))
		{
			ft_putendl_fd("Minishell: builtin: exit: numeric argument required",
				STDERR);
			*ret = 255;
		}
		else if (ft_arrlen(cmd) > 2)
		{
			ft_putendl_fd("Minishell: builtin: exit: too many arguments",
				STDERR);
			return (1);
		}
	}
	return (0);
}

int	my_exit(char **cmd, t_shell *shell)
{
	int	ret;

	ret = 0;
	if (exit_check_arg(cmd, &ret))
		return (1);
	if (ret != 255)
	{
		if (cmd[1])
			ret = ft_atoi(cmd[1]);
		else
			ret = 0;
		ast_free(shell->ast);
	}
	exit (ret);
}

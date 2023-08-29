/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:48:11 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 20:40:12 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtin_dic(char **dict)
{
	*dict++ = ft_strdup("cd");
	*dict++ = ft_strdup("echo");
	*dict++ = ft_strdup("env");
	*dict++ = ft_strdup("exit");
	*dict++ = ft_strdup("export");
	*dict++ = ft_strdup("pwd");
	*dict++ = ft_strdup("unset");
	*dict++ = NULL;
}

char	**builtin_dic(void)
{
	char	**dict;

	dict = malloc (sizeof(char *) * 8);
	init_builtin_dic(dict);
	return (dict);
}

int	is_builtin(char	*cmd)
{
	char	**builtin;
	int		i;

	i = 0;
	builtin = malloc (sizeof(char *) * 8);
	init_builtin_dic(builtin);
	while (builtin[i])
	{
		if (!ft_strcmp(builtin[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(char **cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;

	return (0);
}

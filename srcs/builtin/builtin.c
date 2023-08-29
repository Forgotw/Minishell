/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:48:11 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/29 17:32:39 by lsohler          ###   ########.fr       */
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

char	**builtin_dic()
{
	char	**dict;

	dict = malloc (sizeof(char *) * 8);
	init_builtin_dic(dict);
	return (dict);
}

int	is_builtin(char	*cmd)
{
	char	**builtin;
	int			i;

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

int	my_execve(char **cmd, t_shell *shell)
{
	if (is_builtin(cmd[0]))
		return (exec_builtin(cmd, shell));
	else
		return (execve(get_path(cmd[0]), cmd, shell->env));
	return (-1);
}
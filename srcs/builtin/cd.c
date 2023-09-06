/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:31:13 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 11:53:03 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_pwd_var(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp("OLDPWD=", shell->env[i], ft_strlen("OLDPWD=")))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(ft_strdup("OLDPWD="), shell->oldpath);
		}
		if (!ft_strncmp("PWD=", shell->env[i], ft_strlen("PWD=")))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(ft_strdup("PWD="), shell->path);
		}
		i++;
	}
	return (0);
}

int	change_directory(char **cmd, t_shell *shell)
{
	getcwd(shell->oldpath, 1024);
	if (!cmd[1] || cmd[1][0] == '\0')
	{
		if (chdir(get_env_variable("HOME", shell)))
		{
			ft_putendl_fd("Minishell: cd: HOME not set", STDERR_FILENO);
			return (1);
		}
	}
	else
	{
		if (chdir(cmd[1]))
		{
			perror("Minishell: cd:");
			return (1);
		}
	}
	getcwd(shell->path, 1024);
	change_pwd_var(shell);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:32:04 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 11:44:58 by lsohler          ###   ########.fr       */
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

char	*get_env_variable(char *var, t_shell *shell)
{
	int		len;
	char	*exp_var;
	int		i;

	len = ft_strlen(var);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var, len))
		{
			if (shell->env[i][len] && shell->env[i][len] == '=')
				len++;
			exp_var = ft_strdup(&shell->env[i][len]);
			return (exp_var);
		}
		i++;
	}
	return (NULL);
}

int	env(char **cmd, t_shell *shell)
{
	if (cmd[1])
		return (env_cmd_error());
	else
		return (print_env(shell->env));
}

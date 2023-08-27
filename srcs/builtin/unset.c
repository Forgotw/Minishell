/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:32:30 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/27 17:13:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_identifier(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] == '\0')
		return (1);
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	var_identifier_error(char *str, char *builtin)
{
	if (check_var_identifier(str))
	{
		ft_putstr_fd("Minishell:", STDERR);
		ft_putstr_fd(builtin, STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putendl_fd(BAD_IDENTIFIER, STDERR);
		return (1);
	}
	else
		return (0);
}

void	del_var(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i + 1])
	{
		tmp = env[i];
		env[i] = env[i + 1];
		env[i + 1] = tmp;
		i++;
	}
	free(env[i]);
	env[i] = NULL;
}

void	find_and_del_var(char *str, t_shell *shell)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(str, shell->env[i], len)
			&& (shell->env[i][len + 1] == '\0'
			|| shell->env[i][len + 1] == '='))
		{
			del_var(&shell->env[i]);
			return ;
		}
		i++;
	}
}

int	unset(char	**cmd, t_shell *shell)
{
	int	i;
	int	ret;

	ret = 0;
	if (!cmd[1])
		return (0);
	else
	{
		i = 0;
		while (cmd[i])
		{
			if (var_identifier_error(cmd[i], "export:"))
				ret = 1;
			else
				find_and_del_var(cmd[i], shell);
			i++;
		}
		return (ret);
	}
}

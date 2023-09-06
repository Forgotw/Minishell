/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:32:58 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/06 12:06:05 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_lenght(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (len);
}

char	**add_or_replace_var(char *str, char **shell_env)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	len = export_lenght(str);
	while (shell_env[i])
	{
		if (!ft_strncmp(str, shell_env[i], len)
			&& ((shell_env[i][len + 1] == '\0'
				|| shell_env[i][len + 1] == '=')))
		{
			if (str[len + 1] == '\0')
				return (shell_env);
			tmp = shell_env[i];
			shell_env[i] = ft_strdup(str);
			free(tmp);
			return (shell_env);
		}
		i++;
	}
	shell_env = array_add_str(shell_env, ft_strdup(str));
	return (shell_env);
}

int	export_vars(char **cmd, t_shell *shell)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (cmd[i])
	{
		if (var_identifier_error(cmd[i], "export:"))
			ret = 1;
		else
			shell->env = add_or_replace_var(cmd[i], shell->env);
		i++;
	}
	return (ret);
}

int	print_export(char **shell_env)
{
	int		i;
	char	**sorted;

	i = 0;
	if (!shell_env)
		return (1);
	sorted = ft_arrdup(shell_env);
	ft_arrsort(sorted);
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putendl_fd(sorted[i], STDOUT);
		i++;
	}
	free_array(sorted);
	return (0);
}

int	export(char **cmd, t_shell *shell)
{
	if (!cmd)
		return (-1);
	else if (!cmd[1])
		return (print_export(shell->env));
	else
		return (export_vars(&cmd[1], shell));
	return (0);
}

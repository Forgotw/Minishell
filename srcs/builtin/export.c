/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:32:58 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/27 17:42:51 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_or_replace_var(char *str, t_shell *shell)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	while (str[len] && str[len + 1] != '=')
		len++;
	while (shell->env[i])
	{
		if (!ft_strncmp(str, shell->env[i], len)
			&& (shell->env[i][len + 1] == '\0'
			|| shell->env[i][len + 1] == '='))
		{
			tmp = shell->env[i];
			shell->env[i] = ft_strdup(str);
			free(tmp);
			return ;
		}
		i++;
	}
	shell->env = array_add_str(shell->env, ft_strdup(str));
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
			add_or_replace_var(cmd[i], shell);
		i++;
	}
	return (ret);
}

int	print_export(char **env)
{
	int		i;
	char	**sorted;

	i = 0;
	if (!env)
		return (1);
	sorted = ft_arrdup(env);
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

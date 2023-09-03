/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:48:11 by lsohler           #+#    #+#             */
/*   Updated: 2023/09/03 17:40:11 by lsohler          ###   ########.fr       */
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
		{
			free_array(builtin);
			return (1);
		}
		i++;
	}
	free_array(builtin);
	return (0);
}

int	exec_builtin(char **cmd, t_shell *shell, t_cmd *node)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp("cd", cmd[0]))
		shell->status = change_directory(cmd, shell);
	if (!ft_strcmp("echo", cmd[0]))
	{
		if (node->linktype == PIPE)
		{
			if (node->pid == 0)
				exit (node->shell->status = my_echo(cmd, shell));
		}
		else
			shell->status = my_echo(cmd, shell);
	}
	if (!ft_strcmp("env", cmd[0]))
		shell->status = env(cmd, shell);
	if (!ft_strcmp("exit", cmd[0]))
		shell->status = my_exit(cmd, shell);
	if (!ft_strcmp("export", cmd[0]))
		shell->status = export(cmd, shell);
	if (!ft_strcmp("pwd", cmd[0]))
		shell->status = print_working_directory(cmd, shell);
	if (!ft_strcmp("unset", cmd[0]))
		shell->status = unset(cmd, shell);
	return (0);
}
